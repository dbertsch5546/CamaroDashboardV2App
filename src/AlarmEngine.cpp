// AlarmEngine.cpp

#include <cstring>
#include <fstream>
#include "AlarmEngine.h"
#include "timeout_manager.h"

// Rule constructor implementation
AlarmEngine::AlarmEngine() {
    //Attempt to load rules is they exists
    this->loadRulesFromFile("/home/dbertsch/sensorRules.json");
}
// Add a rule to the alarm engine
int AlarmEngine::addRule(const std::string& sensorName, const std::string& luaScriptPath) {
    //TODO: add more error handling.
    //Create sensorRule data structure
    SensorRule rule;
    rule.sensorName = sensorName;
    //Check if sensor rule already exists
    for(auto& r : sensorRules){
        if(r.sensorName == sensorName){
            std::cerr << "Rule already exists" << std::endl;
            return -1;
        }
    }
    rule.L = luaL_newstate();
    luaL_openlibs(rule.L);
    //Load the script file into the data structure
    FILE* file = fopen(luaScriptPath.c_str(), "r");
    if (file) {
        rule.luaFileContentSize = fread(rule.luaFileContent, 1, sizeof(rule.luaFileContent), file);
        //Get filename and set
        strncpy(rule.luaFileName, luaScriptPath.c_str(), sizeof(rule.luaFileName));
        fclose(file);
    }else{
        return -1;
    }
    //Initialize memory workspace to 0
    memset(rule.memoryWorkspace, 0, sizeof(rule.memoryWorkspace));
    //Add to rules vector
    sensorRules.push_back(rule);
}

SensorRule* AlarmEngine::getRule(const std::string& sensorName){
    for(auto& rule : this->sensorRules){
        if(rule.sensorName == sensorName){
            return &rule;
        }
    }
}

/* Evaluate all added rules, the lua function (psudo C like function) evalutateSensorRule(float sensorValue)
 *
 */
void AlarmEngine::evaluateRules(void *data) {
    gaugeData *currentGaugeData = (gaugeData*)data;
    if(sensorRules.empty()){
        std::cerr << "No rules to evaluate" << std::endl;
        return;
    }
    //Iterate through rules vector
    for(auto& rule : sensorRules){
        char *luaCode = rule.luaFileContent;
        //Load the Lua script
        if(luaL_dofile(rule.L, rule.luaFileName)){//Loading the file each time is not efficient, need to implement this better
            std::cerr << "Error loading script: " << lua_tostring(rule.L, -1) << std::endl;
            continue;
        }
        lua_pushnumber(rule.L, currentGaugeData->injectorDutyCycle);
        lua_setglobal(rule.L, "injectorDutyCycle");
        lua_pushnumber(rule.L, currentGaugeData->oilTemperature);
        lua_setglobal(rule.L, "oilTemperature");
        lua_pushnumber(rule.L, currentGaugeData->coolantTemperature);
        lua_setglobal(rule.L, "coolantTemperature");
        lua_pushnumber(rule.L, currentGaugeData->batteryVoltage);
        lua_setglobal(rule.L, "batteryVoltage");
        lua_pushnumber(rule.L, currentGaugeData->fuelLevel);
        lua_setglobal(rule.L, "fuelLevel");
        lua_pushnumber(rule.L, currentGaugeData->oilPressure);
        lua_setglobal(rule.L, "oilPressure");
        lua_pushnumber(rule.L, currentGaugeData->RPM);
        lua_setglobal(rule.L, "RPM");
        lua_pushnumber(rule.L, currentGaugeData->vehicleSpeed);
        lua_setglobal(rule.L, "vehicleSpeed");
        //Push the Lua function name to be called.
        lua_getglobal(rule.L, "evaluateSensorRule");
        //Check if the function exists
        if(lua_isnil(rule.L, -1)){
            std::cerr << "Function evaluateSensorRule not found in script" << std::endl;
            continue;
        }
        //Push arguments to the Lua function
        lua_pushnumber(rule.L, rule.sensorData);
        //Call the Lua function, we expect 2 results. true/false, message
        if(lua_pcall(rule.L, 1, 2, 0)){
            std::cerr << "Error calling function: " << lua_tostring(rule.L, -1) << std::endl;
            continue;
        }
        //Get the 1st return value.
        bool errorConditionDetected = lua_toboolean(rule.L, -2);
        const char* resultString = lua_tostring(rule.L, -1);
        if(errorConditionDetected){
            /* We need to get this error to the log widget.
             * Call the logHandler function.
             * The logHandler function takes care of notifying the user.
             */
            syslog(LOG_ERR, "%s:%s Error detected", rule.sensorName.c_str(), resultString);
            //Call the log handler
            if(logHandler){
                logHandler(true, resultString);
            }
        }else {
            syslog(LOG_INFO, "%s:%s No error detected", rule.sensorName.c_str(), resultString);
            //Call the log handler
            if(logHandler){
                logHandler(false, resultString);
            }
        }
    }
}

// Update sensor data
int AlarmEngine::updateSensorData(const std::string& sensorName, float data) {
    //Match sensorName
    for (auto& rule : sensorRules) {
        if (rule.sensorName == sensorName) {
            rule.sensorData = data;
            return 0;
        }
    }
}

//Load sensor rules from json file
int AlarmEngine::loadRulesFromFile(const std::string& filename) {
    std::ifstream i(filename);
    if (!i) {
        std::cerr << "File not found" << std::endl;
        return -1;
    }
    json j;
    i >> j; // Read the entire JSON array from the file

    // Check if j is an array and iterate over each element
    if (!j.is_array()) {
        std::cerr << "Invalid JSON format" << std::endl;
        return -1;
    }

    for (auto& element : j) {
        // Access the properties directly from the element
        std::string sensorName = element["sensorName"].get<std::string>();
        std::string luaFileName = element["luaFileName"].get<std::string>();

        // Add the rule using addRule method
        if (!addRule(sensorName, luaFileName)) {
            std::cerr << "Error adding rule" << std::endl;
            return -1;
        }
    }
    return 0; // Return 0 to indicate success
}

//Export sensor rules to json file
int AlarmEngine::saveRulesToFile(const std::string& filename) {
    json j = json::array(); // Create a JSON array

    for (auto& rule : sensorRules) {
        json ruleObject;
        ruleObject["sensorName"] = rule.sensorName;
        ruleObject["luaFileName"] = rule.luaFileName;
        j.push_back(ruleObject); // Add the rule object to the array
    }

    std::ofstream o(filename);
    if (o.is_open()) {
        o << std::setw(4) << j << std::endl; // Write formatted JSON to file
        o.close();
        return 0; // Return 0 to indicate success
    } else {
        return 1; // Return 1 to indicate error opening file
    }
}

void AlarmEngine::setLogHandler(std::function<void(bool errorState, const std::string& message)> handler) {
    logHandler = handler;
}
