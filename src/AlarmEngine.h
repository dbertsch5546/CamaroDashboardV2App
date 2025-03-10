// AlarmEngine.h

#ifndef ALARMENGINE_H
#define ALARMENGINE_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "json.hpp"
#include <functional>
extern "C"{
#include "syslog.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

};
using json = nlohmann::json;

//Define a data structure that holds a sensor rule with attached lua files
struct SensorRule {
    std::string sensorName;
    lua_State *L;
    uint8_t memoryWorkspace[1024];
    char luaFileName[256];
    char luaFileContent[1024*8];
    size_t luaFileContentSize;
    float sensorData;//Most current sensor data
};

struct gaugeData{
    uint16_t    vehicleSpeed;
    uint16_t    RPM;
    uint16_t    oilPressure;
    uint16_t    fuelLevel;
    int         coolantTemperature;
    float       oilTemperature;
    float       batteryVoltage;
    float       injectorDutyCycle;
};

// AlarmEngine class definition
class AlarmEngine {
public:
    //Constructor
    AlarmEngine();
    int addRule(const std::string& sensorName, const std::string& luaScriptPath);
    SensorRule* getRule(const std::string& sensorName);
    int updateSensorData(const std::string& sensorName, float data);
    void evaluateRules(void *data);
    int loadRulesFromFile(const std::string& filename);
    int saveRulesToFile(const std::string& filename);
    void setLogHandler(std::function<void(bool errorState, const std::string& message)> handler);
    std::map<int, std::string> sensorMap = {
            {1, "iacPosition"},
            {2, "batteryVoltage"},
            {3, "RPM"},
            {4, "coolantTemp"},
            {5, "InjectorDutyCycle"},
            {6, "throttlePosition"},
            {7, "mapPressure"},
            {8, "oilPressure"},
            {9, "knockLevel"},
            {10, "knockRetardLevel"},
            {11, "intakeAirTemp"}
    };

private:
    std::vector<SensorRule> sensorRules;
    //The log handler takes a bool (errorState) and a string (message)
    std::function<void(bool errorState, const std::string& message)> logHandler = nullptr;
};

#endif // ALARMENGINE_H
