//
// Created by Dylan Bertsch on 3/3/24.
//

#include "HolleyCANDecoder.h"
#include <linux/can.h>
#include "string.h"

void generateAddress(uint32_t flag, uint32_t cmd, uint32_t targetid, uint32_t targetSerial, uint32_t srcId, uint32_t srcSerial)
{
    uint32_t address = 0x00000000;
    address = srcSerial;
    address = address | (srcId << 11);
    address = address | (targetSerial << 14);
    address = address | (targetid << 25);
    address = address | (cmd << 28);
    int i = 0;
}

HolleyCANDecoder::HolleyCANDecoder()
{
//this->generateCanIDHEX(1312,4,128,3,1);
}
/* Function Name = generateCanIDHEX
 * Description = Generates a Holley EFI can address given parameters.
 */
uint32_t HolleyCANDecoder::generateCanIDHEX(uint32_t sourceSerial, uint32_t sourceID, uint32_t targetSerial, uint32_t targetID, uint32_t command)
{
    HolleyCANDecoder::CanIdType id;
    id.command = command;
    id.flags = 0;
    id.sourceID = sourceID;
    id.sourceSerial = sourceSerial;
    id.targetID = targetID;
    id.targetSerial = targetSerial;

    uint32_t sourceSerialMask = 0x000007FF;
    uint32_t sourceIDMask = 0x00003800;
    uint32_t targetSerialMask = 0x01FFC000;
    uint32_t targetIDMask = 0x0E000000;
    uint32_t commandMask = 0x10000000;

    uint32_t address = 0x00000000;
    address = sourceSerialMask & sourceSerial;
    address = address | (sourceID) << 11;
    address = address | (targetSerial) << 14;
    address = address | (targetID) << 25;
    address = address | (command) << 28;
    return address;
}

uint32_t HolleyCANDecoder::generateCanIDHEX(HolleyCANDecoder::CanIdType id)
{
    uint32_t address = 0x00000000;
    address = id.sourceSerial;
    address = address | (id.sourceID) << 11;
    address = address | (id.targetSerial) << 14;
    address = address | (id.targetID) << 25;
    address = address | (id.command) << 28;
    return address;
}

HolleyCANDecoder::CanIdType HolleyCANDecoder::generateCanID(uint32_t sourceSerial, uint32_t sourceID, uint32_t targetSerial, uint32_t targetID, uint32_t command)
{
    HolleyCANDecoder::CanIdType id;
    id.command = command;
    id.flags = 0;
    id.sourceID = sourceID;
    id.sourceSerial = sourceSerial;
    id.targetID = targetID;
    id.targetSerial = targetSerial;

    uint32_t sourceSerialMask = 0x000007FF;
    uint32_t sourceIDMask = 0x00003800;
    uint32_t targetSerialMask = 0x01FFC000;
    uint32_t targetIDMask = 0x0E000000;
    uint32_t commandMask = 0x10000000;

    uint32_t address = 0x00000000;
    address = sourceSerialMask & sourceSerial;
    address = address | (sourceID) << 11;
    address = address | (targetSerial) << 14;
    address = address | (targetID) << 25;
    address = address | (command) << 28;
    return id;
}

HolleyCANDecoder::can_message HolleyCANDecoder::generateHEFIFrame(HolleyCANDecoder::CanIdType id, char* data, uint8_t DLC)
{
    can_message msg;
    msg.id = id;
    msg.dlc = DLC;
    memcpy(&msg.data,data, DLC);
    return msg;
}

/* Function Name = parseRawCanID
*  Description = Converts a raw id string into its corresponding components for can_id struct
*/
HolleyCANDecoder::CanIdType HolleyCANDecoder::parseRawCanID(string rawID)
{
    HolleyCANDecoder::CanIdType id;
    id.command = 0;
    id.flags = 0;
    id.sourceID = 0;
    id.sourceSerial = 0;
    id.targetID = 0;
    id.targetSerial = 0;

    uint32_t sourceSerialMask = 0x000007FF;
    uint32_t sourceIDMask = 0x00003800;
    uint32_t targetSerialMask = 0x01FFC000;
    uint32_t targetIDMask = 0x0E000000;
    uint32_t commandMask = 0x10000000;

    uint32_t rawID_numeric = stoul(rawID, nullptr, 16);
    id.sourceSerial = rawID_numeric & sourceSerialMask;
    id.sourceID = (rawID_numeric & sourceIDMask) >> 11;
    id.targetSerial = (rawID_numeric & targetSerialMask) >> 14;
    id.targetID = (rawID_numeric & targetIDMask) >> 25;
    id.command = (rawID_numeric & commandMask) >> 28;
    return id;
}
HolleyCANDecoder::CanIdType HolleyCANDecoder::parseRawCanID(uint32_t rawID)
{
    HolleyCANDecoder::CanIdType id;
    id.command = 0;
    id.flags = 0;
    id.sourceID = 0;
    id.sourceSerial = 0;
    id.targetID = 0;
    id.targetSerial = 0;

    uint32_t sourceSerialMask = 0x000007FF;
    uint32_t sourceIDMask = 0x00003800;
    uint32_t targetSerialMask = 0x01FFC000;
    uint32_t targetIDMask = 0x0E000000;
    uint32_t commandMask = 0x10000000;

    id.sourceSerial = rawID & sourceSerialMask;
    id.sourceID = (rawID & sourceIDMask) >> 11;
    id.targetSerial = (rawID & targetSerialMask) >> 14;
    id.targetID = (rawID & targetIDMask) >> 25;
    id.command = (rawID & commandMask) >> 28;
    return id;
}
/* Function Name = writeCANFrame
 * Description = write a can frame to the can bus.
 */
bool HolleyCANDecoder::writeCANFrame(int can_socket, HolleyCANDecoder::can_message msg) {
    //Check that can is initialized
    if(can_socket == -1)
    {
        return false;
    }
    struct can_frame frame;
    frame.can_id = this->generateCanIDHEX(msg.id);
    frame.can_id = frame.can_id | CAN_EFF_FLAG;
    frame.can_dlc = msg.dlc;
    memcpy(&frame.data,&msg.data,msg.dlc);
    int bytes_written = write(can_socket, &frame, sizeof(struct can_frame));
    if(bytes_written < 0){
        perror("Error writing can frame");
        return false;
    }
    return true;
}

/* Function Name = decodeCanDumpFile
*  Description = Converts a candump file into corresponding target serial, source serial, etc components.
*/
vector<HolleyCANDecoder::can_message> HolleyCANDecoder::decodeCanDumpFile(std::string filepath)
{
    ifstream input_file(filepath);
    if (!input_file.is_open())
    {
        cerr << "Candump parser: Unable to open " << filepath << endl;

    }
    string line;
    vector<string> lines;
    while (getline(input_file, line))
    {
        lines.push_back(line);
    }
    vector<can_message> messages;
    for (const auto& i : lines)
    {
        vector<string> words;
        stringstream ss(i);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        //Get the raw ID
        string rawID = words[2].substr(0, words[2].find("#"));
        CanIdType parsedID = this->parseRawCanID(rawID);
        string data = words[2].substr(words[2].find("#")+1);
        int DLC = data.length() / 2;//Determine how many bytes are in CAN frame.
        uint8_t dataArray[8];
        for(int index = 0; index < DLC; index++)
        {
            dataArray[index] = stoul(data.substr(index*2,2),nullptr,16);
        }
        can_message message;
        message.id = parsedID;
        message.dlc = DLC;
        memcpy(&message.data,dataArray,sizeof(dataArray));
        messages.push_back(message);
    }
    return messages;
}
