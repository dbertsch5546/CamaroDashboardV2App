#ifndef PACKETHANDLER_H_
#define PACKETHANDLER_H_

#include <cstdint>
#include <cstddef>
#include <semaphore.h>
#include <vector>
#include <mutex>
#include <atomic>

// Protocol specific constants
#define START_BYTE 0x02
#define END_BYTE 0x03
#define ESCAPE_BYTE 0x7D
#define TRANSFORM_XOR_VALUE 0x20
#define MAX_PACKET_SIZE 1024*1 // Maximum packet size, including header and payload
#define PROTOCOL_MEMORY_CONTEXT_SIZE 1024*1
#define PROTOCOL_HEADER_SERIALIZED_SIZE 12

typedef enum
{
    PACKET_TYPE_DATA = 0,
    PACKET_TYPE_ACK,
    PACKET_TYPE_NACK
} PacketType;

typedef enum
{
    OPERATION_READ = 0,
    OPERATION_WRITE,
    OPERATION_BLOCK_READ,  // New for reading blocks
    OPERATION_BLOCK_WRITE, // New for writing blocks
    OPERATION_EXECUTE      // For function execution
} OperationType;

typedef enum
{
    OPERATION_SUCCESS = 0,
    OPERATION_INVALID_ADDRESS,
    OPERATION_ERROR,
    OPERATION_BUFFER_OVERFLOW,
    OPERATION_SEMAPHORE_TIMEOUT,
    OPERATION_NOT_INITIALIZED
} OperationResult;

typedef enum
{
    WAITING_IDLE,
    WAITING_FOR_ACK,
    WAITING_FOR_DATA,
} PacketReceiveState;

typedef uint8_t FunctionID;
typedef struct __attribute__((packed))
{
    FunctionID functionID;
    uint8_t *parameters; // Flexible array for function parameters
} FunctionExecRequest;

// Function execution response
typedef struct __attribute__((packed))
{
    FunctionID functionID;
    OperationResult result;
    uint8_t *responseData; // Flexible array for response data
} FunctionExecResponse;

// Protocol Header Structure
typedef struct __attribute__((packed))
{
    uint8_t deviceID;
    uint16_t sequenceNumber;
    PacketType packetType;
    OperationType operation;
    uint16_t address;
    uint16_t payloadLength;
    uint8_t integrityCheck;
    OperationResult result;  // Field to store the operation result
    uint8_t flags;           // For future use
} ProtocolHeader;

// Decoder state definitions
typedef enum
{
    DECODER_IDLE,
    DECODER_RECEIVING,
    DECODER_ESCAPE
} DecoderState;

// Decoder context structure for managing state and buffer during decoding
typedef struct __attribute__((packed))
{
    DecoderState state;
    uint8_t *buffer;
    uint16_t bufferLength;
    uint16_t index;
    bool messageComplete;
} DecoderContext;

struct packetWrapper{
    ProtocolHeader header;
    uint8_t *data;
    uint16_t dataSize;
};

class PacketHandler{
public:
    PacketHandler();
    void packetHandlerThread();
    int openSerialPort(const char *port, int baudrate);
    int closeSerialPort();
    OperationResult readServerMemory(uint16_t address, uint8_t *buffer, uint16_t length);
    OperationResult writeServerMemory(uint16_t address, const uint8_t *buffer, uint16_t length);
private:
    int serialPort = -1;
    uint8_t *serverMemoryStorage;
    uint16_t serverMemorySize;
    std::vector<packetWrapper> receivedPackets;
    std::mutex receivedPacketsMutex;
    std::atomic<int> sequenceNumber;
    bool _isInitialized = false;

    int buildPacketMessage(ProtocolHeader *header, uint8_t *payload, uint16_t payloadLength, uint8_t *messageBuffer, uint16_t messageBufferLength);
    int initializePacketServer(uint8_t *_serverMemoryStorage, uint16_t _serverMemorySize);
    int stuffBytes(uint8_t *inputBuffer, uint16_t inputLength, uint8_t *outputBuffer, uint16_t outputLength);
    int serializeProtocolHeader(const ProtocolHeader* header, uint8_t* buffer, size_t bufferSize);
    int deserializeProtocolHeader(const uint8_t* buffer, size_t bufferSize, ProtocolHeader* header);
    int drivePacketReceiveMachine(DecoderContext *context, uint8_t inputByte, uint8_t *outputBuffer, uint16_t outputBufferLength);
    OperationResult waitForACK(uint16_t sequenceNumber);
    OperationResult waitForData(uint16_t sequenceNumber, uint8_t *buffer, uint16_t length);
    uint8_t calculateXORChecksum(const uint8_t *buffer, uint16_t bufferLen);

};


#endif /* PACKETHANDLER_H_ */
