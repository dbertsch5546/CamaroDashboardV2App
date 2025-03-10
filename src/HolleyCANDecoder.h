//
// Created by Dylan Bertsch on 3/3/24.
//

#ifndef CAMARODASHBOARDV2APP_HOLLEYCANDECODER_H
#define CAMARODASHBOARDV2APP_HOLLEYCANDECODER_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include "string.h"
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "unistd.h"

using namespace std;
class HolleyCANDecoder {
public:

    struct CanIdType
    {
        uint32_t flags;
        uint32_t sourceSerial;
        uint32_t sourceID;
        uint32_t targetSerial;
        uint32_t targetID;
        uint32_t command;
    };
    struct can_message
    {
        CanIdType id;
        uint8_t dlc;
        uint8_t data[8];
    };
    HolleyCANDecoder();
    vector<HolleyCANDecoder::can_message> decodeCanDumpFile(string filepath);
    bool writeCANFrame(int can_socket, can_message msg);
    CanIdType parseRawCanID(string rawID);
    CanIdType parseRawCanID(uint32_t rawID);
    uint32_t generateCanIDHEX(uint32_t sourceSerial, uint32_t sourceID, uint32_t targetSerial, uint32_t targetID, uint32_t command);
    uint32_t generateCanIDHEX(CanIdType id);
    CanIdType generateCanID(uint32_t sourceSerial, uint32_t sourceID, uint32_t targetSerial, uint32_t targetID, uint32_t command);
    can_message generateHEFIFrame(CanIdType id, char* data, uint8_t DLC);
private:
    int placeholder = 0;
};


#endif //CAMARODASHBOARDV2APP_HOLLEYCANDECODER_H