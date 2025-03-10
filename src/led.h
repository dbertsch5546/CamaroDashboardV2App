//
// Created by dbertsch on 15/04/24.
//

#ifndef CAMARODASHBOARDV2APP_LED_H
#define CAMARODASHBOARDV2APP_LED_H

#include "stdint.h"
#include "semaphore.h"
#include "stdbool.h"

#define OUTPUT_ERROR_IO_ADDRESS 0x0010
#define OUTPUT_WARNING_IO_ADDRESS 0x0011
#define OUTPUT_BLUE_IO_ADDRESS 0x0012
#define OUTPUT_LED0_IO_ADDRESS 0x0013
#define OUTPUT_LED1_IO_ADDRESS 0x0014
#define OUTPUT_LED2_IO_ADRESSS 0x0015

typedef struct{
    uint8_t errorLED;
    uint8_t warningLED;
    uint8_t blueLED;
    uint8_t greenLED0;
    uint8_t greenLED1;
    uint8_t greenLED2;
}ledStateStruct;

extern ledStateStruct ledStates;

static sem_t ledSemaphore;
static bool _ledSemaphoreInitialized = false;

int setLed(uint16_t address, uint8_t state);
uint8_t getLed(uint16_t address);

#endif //CAMARODASHBOARDV2APP_LED_H
