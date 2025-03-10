//
// Created by development on 06/03/24.
//

#ifndef CAMARODASHBOARDV2APP_GLOBALS_H
#define CAMARODASHBOARDV2APP_GLOBALS_H

#include "GaugeController.h"
#include <atomic>
#include <vector>
#include <linux/can.h>
#include <mutex>
#include "AlarmEngine.h"
#include "utils.h"

extern float batteryVoltage;
extern float rpm;
extern float coolantTemperature;
extern float injectorDutyCycle;
extern float throttlePosition;
extern float map;
extern float oilPressureOhms;
extern float oilPressure;
extern float knockLevel;
extern float knockRetard;
extern float airIntakeTemperature;
extern float iacPosition;
extern float oilTemperatureOhms;
extern float oilTemperatureTempF;


//IO Controller RP2040
extern std::atomic<uint8_t> errorLED;
extern std::atomic<uint8_t> warningLED;
extern std::atomic<uint8_t> okLED;
extern std::atomic<uint8_t> led0;
extern std::atomic<uint8_t> led1;
extern std::atomic<uint8_t> led2;
extern std::atomic<uint8_t> input0;
extern std::atomic<uint8_t> input1;
extern std::atomic<uint8_t> input2;
extern std::atomic<uint8_t> input3;

extern bool _simulateData;

extern std::vector<can_frame> incomingCANFrames;
extern std::vector<can_frame> outgoingCANFrames;
//Protect vectors with a mutex
extern std::mutex incomingCANFramesMutex;
extern std::mutex outgoingCANFramesMutex;

extern AlarmEngine *alarmEngine;
extern CanIOInputHandler canIOInputHandler;
#endif //CAMARODASHBOARDV2APP_GLOBALS_H
