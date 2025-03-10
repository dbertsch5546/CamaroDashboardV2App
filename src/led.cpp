//
// Created by dbertsch on 15/04/24.
//
#include <stdio.h>
#include "led.h"

ledStateStruct ledStates = {0};

int setLed(uint16_t address, uint8_t state){
    if(!_ledSemaphoreInitialized){
        if (sem_init(&ledSemaphore, 0, 1) != 0) {
            perror("sem_init");
            return 1;
        }
        _ledSemaphoreInitialized = true;
    }
    sem_wait(&ledSemaphore);
    if(address == OUTPUT_ERROR_IO_ADDRESS){
        ledStates.errorLED = state;
    }
    else if(address == OUTPUT_WARNING_IO_ADDRESS){
        ledStates.warningLED = state;
    }
    else if(address == OUTPUT_BLUE_IO_ADDRESS){
        ledStates.blueLED = state;
    }
    else if(address == OUTPUT_LED0_IO_ADDRESS){
        ledStates.greenLED0 = state;
    }
    else if(address == OUTPUT_LED1_IO_ADDRESS){
        ledStates.greenLED1 = state;
    }
    else if(address == OUTPUT_LED2_IO_ADRESSS){
        ledStates.greenLED2 = state;
    }
    sem_post(&ledSemaphore);
}

uint8_t getLed(uint16_t address){
    uint8_t state = 0;
    sem_wait(&ledSemaphore);
    if(address == OUTPUT_ERROR_IO_ADDRESS){
        state = ledStates.errorLED;
    }
    else if(address == OUTPUT_WARNING_IO_ADDRESS){
        state = ledStates.warningLED;
    }
    else if(address == OUTPUT_BLUE_IO_ADDRESS){
        state = ledStates.blueLED;
    }
    else if(address == OUTPUT_LED0_IO_ADDRESS){
        state = ledStates.greenLED0;
    }
    else if(address == OUTPUT_LED1_IO_ADDRESS){
        state = ledStates.greenLED1;
    }
    else if(address == OUTPUT_LED2_IO_ADRESSS){
        state = ledStates.greenLED2;
    }
    sem_post(&ledSemaphore);
    return state;
}