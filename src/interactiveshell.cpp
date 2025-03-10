#include "interactiveshell.h"
#include <iostream>
#include "string.h"
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "microshell.h"
#include <vector>
#include <netinet/in.h>
#include "HolleyCANDecoder.h"
#include "globals.h"
#include <filesystem>
namespace fs = std::filesystem;

#define BUF_IN_SIZE    64
#define BUF_OUT_SIZE   64
#define PATH_MAX_SIZE  64

#define INVALID_SOCK -1

int socketfd = INVALID_SOCK;
int serverSocketFD = INVALID_SOCK;

char ush_in_buf[BUF_IN_SIZE];
char ush_out_buf[BUF_OUT_SIZE];
struct ush_object ush;
struct ush_node_object cmd;
struct ush_node_object root;
struct ush_file_descriptor cmd_files[15];

class socketCoutBuffer : public std::streambuf {
private:
    std::vector<char> buffer;

protected:
    virtual int_type overflow(int_type ch) {
        if (ch != EOF) {
            if(socketfd != -1) {
                //Write a char to the socket.
                write(socketfd, &ch, 1);
            }

        }
        return ch;
    }

public:
    const std::vector<char>& getBuffer() const {
        return buffer;
    }

    // For convenience, let's also provide a method to retrieve the buffer as a string
    std::string getString() const {
        return std::string(buffer.begin(), buffer.end());
    }
};

class socketCinBuffer : public std::streambuf {
private:
    char ch;

protected:
    virtual int_type underflow() {
        int clientSocket = socketfd;
        if (clientSocket == -1) {
            return traits_type::eof();  // Corrected EOF handling
        }

        int bytes_read = read(clientSocket, &ch, 1);
        if (bytes_read == 0) {  // Connection closed
            close(clientSocket);
            return traits_type::eof();  // Use traits_type::eof()
        } else if (bytes_read == -1) {  // Error
            // Optionally log the error here
            return traits_type::eof();  // Use traits_type::eof()
        }

        if (ch == '\r') {
            ch = '\n';  // Convert CR to LF
        }

        setg(&ch, &ch, &ch + 1);  // Set buffer pointers

        if (ch != '\r') {  // Echo back non-CR characters
            write(clientSocket, &ch, 1);
        }

        return traits_type::to_int_type(ch);  // Correct return type
    }

public:
    socketCinBuffer(int s){}
};

//Command function prototypes
void canListenerShellCommand(struct ush_object* shellObjectPointer, struct ush_file_descriptor const* fileDescriptor, int argumentCount, char* argumentVector[]);
void luaTestCommand(struct ush_object* shellObjectPointer, struct ush_file_descriptor const* fileDescriptor, int argumentCount, char* argumentVector[]);
void alarmRuleSetupCommand(struct ush_object* shellObjectPointer, struct ush_file_descriptor const* fileDescriptor, int argumentCount, char* argumentVector[]);
void exitCommand(struct ush_object* shellObjectPointer, struct ush_file_descriptor const* fileDescriptor, int argumentCount, char* argumentVector[]);

static int ush_read(struct ush_object *self, char *ch) {
    if (socketfd != -1) {
        //Read a char from the socket.
        int bytes_read = read(socketfd, ch, 1);
        //Check if we received a backspace character.
        if (bytes_read == 0) {
            //Connection closed
            close(socketfd);
            socketfd = INVALID_SOCK;
            ush_deinit(&ush);
            return 0;
        } else if (bytes_read == -1) {
            //Error
            //spdlog::error("Error reading from UNIX socket for shell.");
            return -1;
        } else {
            return 1;
        }
    }
    return -1;
}

static int ush_write(struct ush_object *self, char ch) {
    if (socketfd != -1) {
        //Write a char to the socket.
        ssize_t result = write(socketfd, &ch, 1);
        if(result == -1){
            //gloShellInterface->closeShellClientSocket();
            //spdlog::error("Error writing to shell socket closing.");
            return -1;
        } else {
            return 1;
        }
        //write(gloShellInterface->getShellClientSocket(), &ch, 1);
    }
    return 1;
}
/////////////////
struct ush_io_interface ush_iface = {
        .read = ush_read,
        .write = ush_write
};

struct ush_descriptor ush_desc = {
        .io = &ush_iface,
        .input_buffer = ush_in_buf,
        .input_buffer_size = BUF_IN_SIZE,
        .output_buffer = ush_out_buf,
        .output_buffer_size = BUF_OUT_SIZE,
        .path_max_length = PATH_MAX_SIZE,
        .hostname ="DashV2",
};

InteractiveShell::InteractiveShell() {
    initMicroshell();
}

void InteractiveShell::initMicroshell(){
    //Define shell commands
    cmd_files[0].name = "canListener";
    cmd_files[0].description = "Listens on CAN BUS for Holley EFI data";
    cmd_files[0].exec = canListenerShellCommand;
    cmd_files[1].name = "alarmRuleSetup";
    cmd_files[1].description = "Sets up an alarm rule";
    cmd_files[1].exec = alarmRuleSetupCommand;
    cmd_files[2].name = "luaTest";
    cmd_files[2].description = "Tests Lua scripting";
    cmd_files[2].exec = luaTestCommand;
    cmd_files[3].name = "exit";
    cmd_files[3].description = "Exits the shell";
    cmd_files[3].exec = exitCommand;

    ush_init(&ush, &ush_desc);
    ush_node_mount(&ush, "/", &root, NULL, 0);
    ush_commands_add(&ush, &cmd, cmd_files, 4);
    //Start the thread
    this->_shellThreadHandle = std::thread(&InteractiveShell::shellTask, this);
}

void InteractiveShell::shellTask(){
    printf("Starting shellTask on port %d\r\n", SHELL_PORT);

    struct sockaddr_in server_addr;

    // Create socket
    this->_serverSocketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_serverSocketfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    serverSocketFD = this->_serverSocketfd;
    // Prepare the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // "0.0.0.0"
    server_addr.sin_port = htons(3000); // Port 3000

    // Bind
    if (bind(this->_serverSocketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(this->_serverSocketfd);
        return;
        exit(EXIT_FAILURE);
    }
    // Listen
    if (listen(this->_serverSocketfd, 5) < 0) {
        perror("Listen failed");
        close(this->_serverSocketfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 3000\n");

    // Accept incoming connections (blocking call)
    int client_sock;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    this->_clientSocketfd = accept(this->_serverSocketfd, (struct sockaddr *)&client_addr, &client_len);
    socketfd = this->_clientSocketfd;
    if(client_sock < 0) {
      perror("Accept failed");
      close(this->_clientSocketfd);
      exit(EXIT_FAILURE);
    }
    printf("Connection accepted\n");
    // Close the socket when done
    while(1){
        ush_service(&ush);
        usleep(1000*1);
    }
    // Close sockets after done
    close(this->_clientSocketfd);
    close(this->_serverSocketfd);
}

int InteractiveShell::getClientSocketFD() {
    return this->_clientSocketfd;
}

/****************************Shell Commands**********************************/
#define IAC_CAN_ADDRESS 0x9E06900A
#define BATTERY_VOLTAGE_ADDRESS 0x9E08500A
#define RPM_ADDRESS 0x9E00500A
#define COOLANT_TEMP_ADDRESS 0x9E07D00A
#define INJECTOR_DUTY_CYCLE_ADDRESS 0x9E00D00A
#define THROTTLE_POSITION_ADDRESS 0x9E07500A
#define MAP_ADDRESS 0x9E07100A
#define OIL_PRESSURE_ADDRESS 0x9E08900A
#define KNOCK_LEVEL_ADDRESS 0x9E06100A
#define KNOCK_RETARD_ADDRESS 0x9E05D00A
#define INTAKE_AIR_TEMP_ADDRESS 0x9E07900A

void canListenerShellCommand(struct ush_object* shellObjectPointer, struct ush_file_descriptor const* fileDescriptor, int argumentCount, char* argumentVector[]){
    char ch;
    std::streambuf *originalCoutBuffer = std::cout.rdbuf();
    std::streambuf *originalCinBuffer = std::cin.rdbuf();
    socketCoutBuffer coutBuffer;
    std::cout.rdbuf(&coutBuffer);
    socketCinBuffer cinBuffer(1);
    std::cin.rdbuf(&cinBuffer);
    /*
    //Ask the user for their name
    std::cout << "Enter your name: \r\n";
    std::string name = "";
    while (std::cin.get(ch)) {
        if (ch == '\r')
            std::cout << "\r\n";
            break;
        name += ch;
    }
    std::cout << "Hello, " << name << "!\r\n";
    */
    //Restore the original cout and cin buffers.
    std::cout.rdbuf(originalCoutBuffer);
    std::cin.rdbuf(originalCinBuffer);
}

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// Custom print function
static int custom_print(lua_State *L) {
    //Get socket handle
    int clientSocketHandle = socketfd;
    if(clientSocketHandle == -1){
        return -1;
    }
    int nargs = lua_gettop(L);
    for (int i = 1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            int bytes_written = write(clientSocketHandle, lua_tostring(L, i), strlen(lua_tostring(L, i)));
            //Check for errors
            if(bytes_written < 0){
                return luaL_error(L, "Failed to write to socket");
            }
        }
        else {
            // Fall back to Lua's tostring method
            lua_getglobal(L, "tostring");
            lua_pushvalue(L, i);
            lua_call(L, 1, 1);
            const char *s = lua_tostring(L, -1);
            if(s){
                int bytes_written = write(clientSocketHandle, s, strlen(s));
                //Check for errors
                if(bytes_written < 0){
                    return luaL_error(L, "Failed to write to socket");
                }
            }
            lua_pop(L, 1);
        }
        if (i < nargs){// Tabulate separate args
            int bytes_written = write(clientSocketHandle, "\t", 1);
            //Check for errors
            if(bytes_written < 0){
                return luaL_error(L, "Failed to write to socket");
            }
        }
    }
    //Newline
    int bytes_written = write(clientSocketHandle, "\r\n", 2);
    //Check for errors
    if(bytes_written < 0){
        return luaL_error(L, "Failed to write to socket");
    }
    return 0;
}

//Custom read function
static int custom_read(lua_State *L) {
    // Get socket handle for the shell
    int clientSocketHandle = socketfd;  // Assuming socketfd is defined and valid
    if (clientSocketHandle == -1) {
        return luaL_error(L, "Invalid socket handle");
    }

    char buffer[256];
    int idx = 0; // Current position in the buffer
    char c = 0;  // Character read from socket
    ssize_t n = 0;

    // Read one byte at a time from the socket until we hit a newline
    while ((n = read(clientSocketHandle, &c, 1)) > 0) {
        //Echo the character back to the user
        int bytes_wrtten = write(clientSocketHandle, &c, 1);
        //Check for error
        if(bytes_wrtten < 0){
            return luaL_error(L, "Failed to write to socket");
        }
        // Append the character to the buffer if it's not a newline
        if (c == '\r') {
            //Write
            int bytes_written = write(clientSocketHandle, "\r\n", 2);
            //Check for errors
            if(bytes_written < 0){
                return luaL_error(L, "Failed to write to socket");
            }
            break; // Stop reading if newline
        }
        buffer[idx++] = c;

        // Check to prevent buffer overflow
        if (idx >= sizeof(buffer) - 1) {
            break; // Stop reading to avoid buffer overflow
        }
    }

    // Handle read errors
    if (n < 0) {
        return luaL_error(L, "Failed to read from socket");
    }

    // Null terminate the string read into buffer
    buffer[idx] = '\0';

    // Push the string onto the Lua stack
    lua_pushstring(L, buffer);
    return 1; // Return one result
}

void exitCommand(struct ush_object* shellObjectPointer, struct ush_file_descriptor const* fileDescriptor, int argumentCount, char* argumentVector[]){
    // Close the socket
    close(socketfd);
    close(serverSocketFD);
    socketfd = INVALID_SOCK;
    // Deinitialize the microshell
    ush_deinit(&ush);
}

void luaTestCommand(struct ush_object* shellObjectPointer, struct ush_file_descriptor const* fileDescriptor, int argumentCount, char* argumentVector[]){
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Register the custom print function
    lua_pushcfunction(L, custom_print);
    lua_setglobal(L, "print");

    // Register the custom read function
    lua_pushcfunction(L, custom_read);
    lua_setglobal(L, "read");

    // Example Lua code to use these functions
    const char* lua_code =
            "print('Enter some text:')\n"
            "local input = read()\n"
            "print('You entered:', input)";

    if (luaL_dostring(L, lua_code) != LUA_OK) {
        fprintf(stderr, "Error executing Lua code: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
}
#define IAC_CAN_ADDRESS 0x9E06900A
#define BATTERY_VOLTAGE_ADDRESS 0x9E08500A
#define RPM_ADDRESS 0x9E00500A
#define COOLANT_TEMP_ADDRESS 0x9E07D00A
#define INJECTOR_DUTY_CYCLE_ADDRESS 0x9E00D00A
#define THROTTLE_POSITION_ADDRESS 0x9E07500A
#define MAP_ADDRESS 0x9E07100A
#define OIL_PRESSURE_ADDRESS 0x9E08900A
#define KNOCK_LEVEL_ADDRESS 0x9E06100A
#define KNOCK_RETARD_ADDRESS 0x9E05D00A
#define INTAKE_AIR_TEMP_ADDRESS 0x9E07900A
void alarmRuleSetupCommand(struct ush_object* shellObjectPointer, struct ush_file_descriptor const* fileDescriptor, int argumentCount, char* argumentVector[]){
    char ch;
    std::streambuf *originalCoutBuffer = std::cout.rdbuf();
    std::streambuf *originalCinBuffer = std::cin.rdbuf();
    socketCoutBuffer coutBuffer;
    std::cout.rdbuf(&coutBuffer);
    socketCinBuffer cinBuffer(1);
    std::cin.rdbuf(&cinBuffer);

    // Present a list of sensors
    std::cout << "Select a sensor by number:\r\n";
    std::cout << "1. IAC Position\r\n";
    std::cout << "2. Battery Voltage\r\n";
    std::cout << "3. RPM\r\n";
    std::cout << "4. Coolant Temperature\r\n";
    std::cout << "5. Injector Duty Cycle\r\n";
    std::cout << "6. Throttle Position\r\n";
    std::cout << "7. MAP Pressure\r\n";
    std::cout << "8. OIL Pressure\r\n";
    std::cout << "9. Knock Level\r\n";
    std::cout << "10. Knock Retard Level\r\n";
    std::cout << "11. Intake Air Temperature\r\n";

    std::string sensorChoice;
    std::getline(std::cin, sensorChoice);
    std::cout << "You selected sensor number: " << sensorChoice << "\r\n";
    //Convert sensorChoice into the mapped sensor name
    //TODO: Need to make sure to handle error for invalid input...
    sensorChoice = alarmEngine->sensorMap[std::stoi(sensorChoice)];
    // Prompt for a Lua file path
    std::cout << "Enter the Lua file path for the sensor rules: ";
    std::string filePath;
    //Clear cin input buffer

    std::getline(std::cin, filePath);  // Reads input until a newline is encountered


    std::cout << "File path entered: " << filePath << "\r\n";
    //Verify the file exists, and if it does load it into a C++ string
    if (fs::exists(filePath)) {
        std::cout << "File path verified.\r\n";
        alarmEngine->addRule(sensorChoice, filePath);
        alarmEngine->saveRulesToFile("/home/dbertsch/sensorRules.json");
    } else {
        std::cout << "File path does not exist.\r\n";
    }

    // Restore the original cout and cin buffers.
    std::cout.rdbuf(originalCoutBuffer);
    std::cin.rdbuf(originalCinBuffer);
}