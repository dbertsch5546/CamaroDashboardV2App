//
// Created by dbertsch on 22/05/24.
//

#ifndef CAMARODASHBOARDV2APP_UTILS_H
#define CAMARODASHBOARDV2APP_UTILS_H

#include <iostream>
#include <mutex>
#include <unordered_map>
#include <stdexcept>

#include <iostream>
#include <mutex>
#include <unordered_map>
#include <stdexcept>

struct CanIOInputStruct {
    float input1 = 0.0f;
    float input2 = 0.0f;
    float input3 = 0.0f;
    float input4 = 0.0f;
    float input5 = 0.0f;
    float input6 = 0.0f;
    float input7 = 0.0f;
    float input8 = 0.0f;
    float output1 = 0.0f;
    float output2 = 0.0f;
    float output3 = 0.0f;
    float output4 = 0.0f;
    float output5 = 0.0f;
    float output6 = 0.0f;
    float output7 = 0.0f;
    float output8 = 0.0f;
};

class CanIOInputHandler {

public:
    enum valueType {
        INPUT,//INPUT is an input to the ECU
        OUTPUT//OUTPUT is an output from the ECU
    };
    // Add a new spoof serial number
    void addSerialNumber(uint32_t serialNumber) {
        std::lock_guard<std::mutex> lock(mtx);
        if (dataMap.find(serialNumber) != dataMap.end()) {
            throw std::runtime_error("Serial number already exists");
        }
        dataMap[serialNumber] = CanIOInputStruct{};
    }

    // Set values for a specific serial number
    void setValue(uint32_t serialNumber, const CanIOInputStruct& newData) {
        std::lock_guard<std::mutex> lock(mtx);
        if (dataMap.find(serialNumber) == dataMap.end()) {
            throw std::runtime_error("Serial number not found");
        }
        dataMap[serialNumber] = newData;
    }

    void setValue(uint32_t serialNumber, int channelIndex, float value, valueType type) {
        std::lock_guard<std::mutex> lock(mtx);
        if (dataMap.find(serialNumber) == dataMap.end()) {
            throw std::runtime_error("Serial number not found");
        }

        auto& data = dataMap[serialNumber];
        switch (channelIndex) {
            case 1:
                if (type == valueType::OUTPUT) {
                    data.output1 = value;
                } else {
                    data.input1 = value;
                }
                break;
            case 2:
                if (type == valueType::OUTPUT) {
                    data.output2 = value;
                } else {
                    data.input2 = value;
                }
                break;
            case 3:
                if (type == valueType::OUTPUT) {
                    data.output3 = value;
                } else {
                    data.input3 = value;
                }
                break;
            case 4:
                if (type == valueType::OUTPUT) {
                    data.output4 = value;
                } else {
                    data.input4 = value;
                }
                break;
            case 5:
                if (type == valueType::OUTPUT) {
                    data.output5 = value;
                } else {
                    data.input5 = value;
                }
                break;
            case 6:
                if (type == valueType::OUTPUT) {
                    data.output6 = value;
                } else {
                    data.input6 = value;
                }
                break;
            case 7:
                if (type == valueType::OUTPUT) {
                    data.output7 = value;
                } else {
                    data.input7 = value;
                }
                break;
            case 8:
                if (type == valueType::OUTPUT) {
                    data.output8 = value;
                } else {
                    data.input8 = value;
                }
                break;
            default:
                throw std::invalid_argument("Invalid channel index");
        }
    }


    // Get value for a specific serial number and channel index
    float getValue(uint32_t serialNumber, int channelIndex) {
        std::lock_guard<std::mutex> lock(mtx);
        if (dataMap.find(serialNumber) == dataMap.end()) {
            throw std::runtime_error("Serial number not found");
        }

        const auto& data = dataMap[serialNumber];
        switch (channelIndex) {
            case 1: return data.input1;
            case 2: return data.input2;
            case 3: return data.input3;
            case 4: return data.input4;
            case 5: return data.input5;
            case 6: return data.input6;
            case 7: return data.input7;
            case 8: return data.input8;
            default: throw std::invalid_argument("Invalid channel index");
        }
    }

    // Debug function to print the state of the struct for a specific serial number
    void printState(uint32_t serialNumber) {
        std::lock_guard<std::mutex> lock(mtx);
        if (dataMap.find(serialNumber) == dataMap.end()) {
            throw std::runtime_error("Serial number not found");
        }
        const auto& data = dataMap[serialNumber];
        std::cout << "Serial Number: " << serialNumber << "\n"
                  << "input1: " << data.input1 << ", "
                  << "input2: " << data.input2 << ", "
                  << "input3: " << data.input3 << ", "
                  << "input4: " << data.input4 << ", "
                  << "input5: " << data.input5 << ", "
                  << "input6: " << data.input6 << ", "
                  << "input7: " << data.input7 << ", "
                  << "input8: " << data.input8 << "\n";
    }

    // Debug function to print the state of all structs
    void printAllStates() {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& pair : dataMap) {
            uint32_t serialNumber = pair.first;
            const auto& data = pair.second;
            std::cout << "Serial Number: " << serialNumber << "\n"
                      << "input1: " << data.input1 << ", "
                      << "input2: " << data.input2 << ", "
                      << "input3: " << data.input3 << ", "
                      << "input4: " << data.input4 << ", "
                      << "input5: " << data.input5 << ", "
                      << "input6: " << data.input6 << ", "
                      << "input7: " << data.input7 << ", "
                      << "input8: " << data.input8 << "\n";
        }
    }

private:
    std::unordered_map<uint32_t, CanIOInputStruct> dataMap;
    std::mutex mtx;
};

#endif //CAMARODASHBOARDV2APP_UTILS_H
