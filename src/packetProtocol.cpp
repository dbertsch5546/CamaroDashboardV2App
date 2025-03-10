#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include "stdbool.h"
#include <stddef.h>
#include <stdint.h>
#include <semaphore.h>
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <unistd.h>     // UNIX standard function definitions
#include <cstring>
#include <thread>
#include "packetProtocol.h"

PacketHandler::PacketHandler() {
    this->sequenceNumber = 0;
    //Initialize serverMemoryStorage with malloc of 1024 bytes
    char *serverMemoryStorage = (char *) malloc(1024);
    if (serverMemoryStorage == nullptr) {
        printf("Failed to allocate server memory storage\n");
    }
    if (initializePacketServer((uint8_t *) serverMemoryStorage, 1024) != 0) {
        printf("Failed to initialize packet server\n");
    }
    //Open serial port
    int result = openSerialPort("/dev/ttyAMA0", B115200);
    //Start the packet handler thread
    std::thread packetHandlerThread(&PacketHandler::packetHandlerThread, this);
    auto handle = packetHandlerThread.native_handle();
    pthread_setname_np(handle, "PacketHandlerThread");
    packetHandlerThread.detach();
    this->_isInitialized = true;
}

int PacketHandler::initializePacketServer(uint8_t *_serverMemoryStorage, uint16_t _serverMemorySize) {
    //Ensure that the serverMemoryStorage is not null
    if(_serverMemoryStorage == nullptr){
        printf("Server Memory Storage is null\n");
        return -1;
    }
    //Ensure that the serverMemorySize is not 0
    if(_serverMemorySize == 0){
        printf("Server Memory Size is 0\n");
        return -1;
    }
    this->serverMemoryStorage = _serverMemoryStorage;
    this->serverMemorySize = _serverMemorySize;
    return 0;
}

OperationResult PacketHandler::waitForACK(uint16_t sequenceNumber) {
    auto startTime = std::chrono::steady_clock::now();  // Record start time
    auto timeout = std::chrono::seconds(1);             // Define a 1-second timeout

    // Scan through received packets vector until we find the ACK with the same sequence number or timeout
    while (std::chrono::steady_clock::now() - startTime < timeout) {
        if (this->receivedPacketsMutex.try_lock()) {
            for (int index = 0; index < this->receivedPackets.size(); index++) {
                if (this->receivedPackets[index].header.packetType == PACKET_TYPE_ACK && this->receivedPackets[index].header.sequenceNumber == sequenceNumber) {
                    //Remove the packet from the received packets vector
                    this->receivedPackets.erase(this->receivedPackets.begin() + index);
                    this->receivedPacketsMutex.unlock();
                    return OPERATION_SUCCESS;  // Successfully found the ACK packet
                }
            }
            this->receivedPacketsMutex.unlock();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Sleep briefly to reduce busy waiting
        }
    }

    return OPERATION_NOT_INITIALIZED;  // Timeout reached without finding ACK
}

OperationResult PacketHandler::waitForData(uint16_t sequenceNumber, uint8_t *buffer, uint16_t length) {
    auto startTime = std::chrono::steady_clock::now();  // Record start time
    auto timeout = std::chrono::seconds(30);             // Define a 1-second timeout

    // Scan through received packets vector until we find the ACK with the same sequence number or timeout
    while (std::chrono::steady_clock::now() - startTime < timeout) {
        if (this->receivedPacketsMutex.try_lock()) {
            for (int index = 0; index < this->receivedPackets.size(); index++) {
                if (this->receivedPackets[index].header.packetType == PACKET_TYPE_DATA &&
                    this->receivedPackets[index].header.sequenceNumber == sequenceNumber) {
                    if (this->receivedPackets[index].dataSize == length) {
                        memcpy(buffer, this->receivedPackets[index].data, length);
                        //Erase the packet from the received packets vector
                        this->receivedPackets.erase(this->receivedPackets.begin() + index);
                        this->receivedPacketsMutex.unlock();
                        return OPERATION_SUCCESS;  // Successfully found the data packet
                    }
                }
            }
            this->receivedPacketsMutex.unlock();
            std::this_thread::yield();  // Yield to other threads
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Sleep briefly to reduce busy waiting
        }
    }

    return OPERATION_NOT_INITIALIZED;  // Timeout reached without finding data packet
}

int PacketHandler::openSerialPort(const char *port, int baudrate) {
    int _serialPort = open(port, O_RDWR | O_NOCTTY);
    if (_serialPort == -1) {
        printf("Error opening serial port: %s\n", strerror(errno));
        return -1;
    }
    this->serialPort = _serialPort;
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(_serialPort, &tty) != 0) {
        perror("Error from tcgetattr");
        close(_serialPort);
        return -1;
    }

    cfsetospeed(&tty, B230400);
    cfsetispeed(&tty, B230400);

    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CSIZE;  // Clear the mask
    tty.c_cflag |= CS8;     // 8 data bits

    tty.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable special handling of received bytes

    tty.c_oflag &= ~OPOST; // Raw output

    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN); // Disable echoing and canonical mode

    tty.c_cc[VMIN] = 0; // Minimum number of characters to read
    tty.c_cc[VTIME] = 1000; // Timeout in deciseconds for read

    if (tcsetattr(_serialPort, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        close(_serialPort);
        return -1;
    }

    return _serialPort;
}

int PacketHandler::closeSerialPort() {
    //Close the serial port
    if(serialPort != -1){
        close(serialPort);
    }
    return 0;
}

int PacketHandler::stuffBytes(uint8_t *inputBuffer, uint16_t inputLength, uint8_t *outputBuffer, uint16_t outputLength) {
    if (inputBuffer == NULL || outputBuffer == NULL) {
        return -1; // Error, null pointer
    }

    uint16_t outputIndex = 0;
    for (uint16_t i = 0; i < inputLength; ++i) {
        uint8_t currentByte = inputBuffer[i];
        // Check if the byte is a special character
        if (currentByte == START_BYTE || currentByte == END_BYTE || currentByte == ESCAPE_BYTE) {
            if (outputIndex >= outputLength - 1) {
                return -2; // Error, output buffer overflow
            }
            // Insert escape byte and transform the current byte
            outputBuffer[outputIndex++] = ESCAPE_BYTE;
            outputBuffer[outputIndex++] = currentByte ^ TRANSFORM_XOR_VALUE;
        } else {
            if (outputIndex >= outputLength) {
                return -2; // Error, output buffer overflow
            }
            outputBuffer[outputIndex++] = currentByte;
        }
    }
    return outputIndex; // Return the length of the stuffed buffer
}

int PacketHandler::serializeProtocolHeader(const ProtocolHeader *header, uint8_t *buffer, size_t bufferSize) {
    const size_t requiredSize = 12; // Explicit total size

    if (bufferSize < requiredSize) {
        return -1; // Buffer not large enough
    }

    buffer[0] = header->deviceID;
    buffer[1] = header->sequenceNumber & 0xFF;
    buffer[2] = (header->sequenceNumber >> 8) & 0xFF;
    buffer[3] = header->packetType;
    buffer[4] = header->operation;
    buffer[5] = header->address & 0xFF;
    buffer[6] = (header->address >> 8) & 0xFF;
    buffer[7] = header->payloadLength & 0xFF;
    buffer[8] = (header->payloadLength >> 8) & 0xFF;
    buffer[9] = header->integrityCheck;
    buffer[10] = header->result;
    buffer[11] = header->flags;

    return requiredSize; // Number of bytes written
}

int PacketHandler::deserializeProtocolHeader(const uint8_t *buffer, size_t bufferSize, ProtocolHeader *header) {
    const size_t requiredSize = 12; // Explicit total size

    if (bufferSize < requiredSize) {
        return -1; // Buffer does not contain enough data
    }

    header->deviceID = buffer[0];
    header->sequenceNumber = buffer[1] | (buffer[2] << 8);
    header->packetType = (PacketType) buffer[3];
    header->operation = (OperationType) buffer[4];
    header->address = buffer[5] | (buffer[6] << 8);
    header->payloadLength = buffer[7] | (buffer[8] << 8);
    header->integrityCheck = buffer[9];
    header->result = (OperationResult) buffer[10];
    header->flags = buffer[11];

    return requiredSize; // Number of bytes read
}

uint8_t PacketHandler::calculateXORChecksum(const uint8_t *buffer, uint16_t bufferLen) {
    uint8_t checksum = 0;
    for (uint16_t i = 0; i < bufferLen; ++i) {
        checksum ^= buffer[i];
    }
    return checksum;
}

int PacketHandler::drivePacketReceiveMachine(DecoderContext *context, uint8_t inputByte, uint8_t *outputBuffer, uint16_t outputBufferLength) {
    // Check if the context is NULL
    if (context == NULL) {
        printf("drivePacketReceiveMachine: context is null\n");
        return -1;
    }

    // Check if the outputBuffer is NULL
    if (outputBuffer == NULL) {
        printf("drivePacketReceiveMachine: outputBuffer is null\n");
        return -1; // Added return statement for consistency
    }

    switch (context->state) {
        case DECODER_IDLE:
            if (inputByte == START_BYTE) {
                context->index = 0;
                context->state = DECODER_RECEIVING;
            }
            break;

        case DECODER_RECEIVING:
            if (inputByte == END_BYTE) {
                context->messageComplete = true;
                context->state = DECODER_IDLE; // Reset state-machine

                // Check checksum validity
                if (context->index <= PROTOCOL_HEADER_SERIALIZED_SIZE) {
                    return -3; // Underflow
                }

                ProtocolHeader header = {0};
                ProtocolHeader *receivedHeader = (ProtocolHeader *)&header;
                int deserializeResult = deserializeProtocolHeader(outputBuffer, PROTOCOL_HEADER_SERIALIZED_SIZE, receivedHeader);
                // context->index should equal 40 (ProtocolHeader) + payloadLength + 1 (checksum)
                if (receivedHeader->operation == OPERATION_READ && receivedHeader->flags == 1) {
                    // Do not count the payload length, payload length tells us how many bytes to read from the server memory context.
                    if (context->index != PROTOCOL_HEADER_SERIALIZED_SIZE + 1) {
                        printf("drivePacketReceiveMachine: underflow\n");
                        return -3; // Underflow
                    }
                } else {
                    if (context->index != PROTOCOL_HEADER_SERIALIZED_SIZE + receivedHeader->payloadLength + 1) {
                        printf("drivePacketReceiveMachine: underflow\n");
                        return -3; // Underflow
                    }
                }

                uint8_t *receivedPayload = outputBuffer + PROTOCOL_HEADER_SERIALIZED_SIZE;
                volatile uint8_t contestedChecksum = 0x00;
                volatile uint8_t computedChecksum = 0x00;

                if (receivedHeader->operation == OPERATION_READ && receivedHeader->flags == 1) {
                    contestedChecksum = outputBuffer[PROTOCOL_HEADER_SERIALIZED_SIZE];
                    computedChecksum = calculateXORChecksum(outputBuffer, PROTOCOL_HEADER_SERIALIZED_SIZE);
                } else {
                    contestedChecksum = outputBuffer[PROTOCOL_HEADER_SERIALIZED_SIZE + receivedHeader->payloadLength];
                    computedChecksum = calculateXORChecksum(outputBuffer, PROTOCOL_HEADER_SERIALIZED_SIZE + receivedHeader->payloadLength);
                }

                if (contestedChecksum != computedChecksum) {
                    printf("drivePacketReceiveMachine: checksum error\n");
                    return -4; // Checksum error;
                }
                //Call the packet received callback in addition to returning 1 back to the user.
                /*
                if(_packetReceivedCallback != NULL){
                    //Not sure if needed anymore.
                    //_packetReceivedCallback(receivedHeader, receivedPayload, receivedHeader->payloadLength);
                }
                */
                return 1; // Successfully received a complete message
            } else if (inputByte == ESCAPE_BYTE) {
                context->state = DECODER_ESCAPE;
            } else {
                if (context->index >= outputBufferLength) {
                    printf("drivePacketReceiveMachine: outputBuffer overflow\n");
                    return -2;
                }
                outputBuffer[context->index++] = inputByte;
            }
            break;

        case DECODER_ESCAPE:
            if (context->index >= outputBufferLength) {
                return -2; // Error, output buffer overflow
            }
            outputBuffer[context->index++] = inputByte ^ TRANSFORM_XOR_VALUE;
            context->state = DECODER_RECEIVING;
            break;
    }

    return 0; // Message still in progress or no message yet started.
}

//Thread that drives the packet handler.
void PacketHandler::packetHandlerThread() {
    //Create a decoder context
    DecoderContext decoderContext;
    memset(&decoderContext, 0, sizeof(DecoderContext));
    decoderContext.buffer = (uint8_t*)malloc(1024*8);
    if(decoderContext.buffer == nullptr){
        printf("Failed to allocate decoder buffer\n");
        return;
    }
    decoderContext.bufferLength = 1024*8;
    uint8_t receivedPacketBuffer[1024];
    while(1){
        //Ensure that serial port is open
        if(serialPort < 0){
            printf("Serial port is not open\n");
            usleep(1000*100);
            continue;
        }
        //Read data from the serial port
        uint8_t receivedBuffer[1024*8] = {0};
        int bytes_read = read(serialPort, receivedBuffer, sizeof(receivedBuffer));
        //printf("Received %d bytes\n", bytes_read);
        //Drive the packet receive machine
        if(bytes_read > 0){
            for(int index = 0; index < bytes_read; index++){
                if(drivePacketReceiveMachine(&decoderContext, receivedBuffer[index], receivedPacketBuffer, sizeof(receivedPacketBuffer))){
                    //Decode the packet
                    ProtocolHeader receivedHeader = {0};
                    packetWrapper packet = {0};
                    int headerSize = deserializeProtocolHeader(receivedPacketBuffer, sizeof(receivedPacketBuffer), &receivedHeader);

                    if(headerSize < 0){
                        printf("Error deserializing header\n");
                        continue;
                    }
                    if(receivedHeader.payloadLength > 0){
                        std::lock_guard<std::mutex> lock(receivedPacketsMutex);
                        packet.header = receivedHeader;
                        packet.data = (uint8_t*)malloc(receivedHeader.payloadLength);
                        memcpy(packet.data, receivedPacketBuffer + headerSize, receivedHeader.payloadLength);
                        packet.dataSize = receivedHeader.payloadLength;
                        //Add the received packet to the received packet queue
                        receivedPackets.push_back(packet);
                    }else{
                        std::lock_guard<std::mutex> lock(receivedPacketsMutex);
                        packet.header = receivedHeader;
                        packet.data = NULL;
                        packet.dataSize = 0;
                        //Add the received packet to the received packet queue
                        receivedPackets.push_back(packet);
                    }
                }
            }
            usleep(1000);
        }
        usleep(1000*10);
    }
}

int PacketHandler::buildPacketMessage(ProtocolHeader *header, uint8_t *payload, uint16_t payloadLength, uint8_t *messageBuffer, uint16_t messageBufferLength) {
    if (header == NULL || messageBuffer == NULL) {
        return -1; // Error, null pointer
    }
    header->payloadLength = payloadLength;

    memset(messageBuffer, 0, messageBufferLength);
    uint8_t headerBuffer[PROTOCOL_HEADER_SERIALIZED_SIZE+32];//Hack need to do proper size checking!
    volatile int serializedBytes = serializeProtocolHeader(header, headerBuffer, sizeof(headerBuffer));
    // Create a buffer for header and payload combined
    uint8_t combinedBuffer[serializedBytes + payloadLength];
    memcpy(combinedBuffer, headerBuffer, serializedBytes);
    if (payload != NULL && payloadLength > 0) {
        memcpy(combinedBuffer + serializedBytes, payload, payloadLength);
    }

    // Calculate the checksum over the combined header and payload
    //If the operation is a read, the payload length is 0, so we do not include the payload in the checksum.
    uint8_t checksum = 0x00;
    if(header->operation == OPERATION_READ && header->flags == 1){
        //Flag of 1 indicates that the payload length is just the number of bytes to read from the server memory context.
        checksum = calculateXORChecksum(combinedBuffer, serializedBytes);
    }else{
        checksum = calculateXORChecksum(combinedBuffer, serializedBytes + payloadLength);
    }

    // Ensure the combined length of header, payload, checksum, and start/end bytes is within limits
    if (serializedBytes + payloadLength + 1 + 2 > messageBufferLength) {
        printf("buildPacketMessage: Output buffer too small. Need %d bytes, but buffer is %d bytes in size.\n", sizeof(headerBuffer) + payloadLength + 1 + 2, messageBufferLength);
        return -3; // Error, message buffer overflow
    }

    // Start byte
    uint16_t messageLength = 0;
    messageBuffer[messageLength++] = START_BYTE;

    // Add header
    memcpy(messageBuffer + messageLength, headerBuffer, serializedBytes);
    messageLength += serializedBytes;

    // Add payload if it exists
    if(payload != NULL){
        memcpy(messageBuffer + messageLength, payload, payloadLength);
        messageLength += payloadLength;
    }

    // Add checksum
    messageBuffer[messageLength++] = checksum;

    // End byte
    messageBuffer[messageLength++] = END_BYTE;

    // Apply byte stuffing to the entire packet (except start and end bytes)
    uint8_t stuffedMessage[MAX_PACKET_SIZE];
    int stuffedLength = stuffBytes(messageBuffer + 1, messageLength - 2, stuffedMessage, sizeof(stuffedMessage));
    if (stuffedLength < 0) {
        return -4; // Error, stuffing failed
    }

    // Reassemble the packet with start byte, stuffed data, and end byte
    messageBuffer[0] = START_BYTE;
    memcpy(messageBuffer + 1, stuffedMessage, stuffedLength);
    messageBuffer[1 + stuffedLength] = END_BYTE;

    return stuffedLength + 2;
}

OperationResult PacketHandler::writeServerMemory(uint16_t address, const uint8_t *buffer, uint16_t length) {
    if(!this->_isInitialized){
        return OPERATION_NOT_INITIALIZED;
    }
    //Check that serial port is open
    if(serialPort < 0){
        return OPERATION_ERROR;
    }
    //Create packet according to what the user wants to write
    ProtocolHeader header = {0};
    header.deviceID = 0x01;
    header.sequenceNumber = this->sequenceNumber;
    header.packetType = PACKET_TYPE_DATA;
    header.operation = OPERATION_WRITE;
    header.address = address;
    header.payloadLength = length;
    header.integrityCheck = 0;
    header.result = OPERATION_SUCCESS;
    header.flags = 0;
    //Set packet flag to 1 if more than 1 byte is to be written.
    if(length > 0){
        header.flags = 1;
    }
    //Create a buffer to hold the packet
    uint8_t packetBuffer[MAX_PACKET_SIZE] = {0};
    //Build the packet
    int packetSize = buildPacketMessage(&header, (uint8_t*)buffer, length, packetBuffer, sizeof(packetBuffer));
    if(packetSize < 0){
        return OPERATION_ERROR;
    }
    //Make sure to increment the sequence number
    this->sequenceNumber++;
    //Write the packet to the serial port
    int bytesWritten = write(this->serialPort, packetBuffer, packetSize);
    //usleep(1000*25);
    if(bytesWritten < 0){
        return OPERATION_ERROR;
    }
    //Wait for an ack to be received, the ack will have the same sequence number as the packet sent.
    ProtocolHeader ackHeader = {0};
    uint8_t ackData[32] = {0};
    OperationResult ackResult = waitForACK(header.sequenceNumber);
    if(ackResult != OPERATION_SUCCESS){
        return OPERATION_ERROR;
    }
    return OPERATION_SUCCESS;

}

OperationResult PacketHandler::readServerMemory(uint16_t address, uint8_t *buffer, uint16_t length) {
    if(!this->_isInitialized){
        return OPERATION_NOT_INITIALIZED;
    }
    //Check if serial port is open
    if(serialPort < 0){
        return OPERATION_ERROR;
    }
    //Create packet according to what the user wants to read
    ProtocolHeader header = {0};
    header.deviceID = 0x01;
    header.sequenceNumber = this->sequenceNumber;
    header.packetType = PACKET_TYPE_DATA;
    header.operation = OPERATION_READ;
    header.address = address;
    header.payloadLength = length;
    header.integrityCheck = 0;
    header.result = OPERATION_SUCCESS;
    header.flags = 0;
    //Set packet flag to 1 if more than 1 byte is to be read.
    if(length > 0){
        header.flags = 1;
    }
    //Create a buffer to hold the packet
    uint8_t packetBuffer[MAX_PACKET_SIZE] = {0};
    //Build the packet
    int packetSize = buildPacketMessage(&header, NULL, length, packetBuffer, sizeof(packetBuffer));
    if(packetSize < 0){
        return OPERATION_ERROR;
    }
    //Write the packet to the serial port
    int bytes_written = write(serialPort, packetBuffer, packetSize);
    //usleep(1000*25);
    if(bytes_written < 0){
        return OPERATION_ERROR;
    }
    //Wait for the ACK, it will have the same sequence number as the packet we just sent.
    OperationResult result = waitForACK(header.sequenceNumber);
    if(result != OPERATION_SUCCESS){
        return result;
    }
    //Wait for the data packet, it will have the ack sequence number + 1
    result = waitForData(header.sequenceNumber + 1, buffer, length);
    if(result != OPERATION_SUCCESS){
        return result;
    }
    return OPERATION_SUCCESS;
}
