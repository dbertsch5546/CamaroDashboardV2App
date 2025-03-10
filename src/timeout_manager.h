#ifndef TIMEOUT_MANAGER_H
#define TIMEOUT_MANAGER_H

#include <stdbool.h>
#include <time.h>

// Struct to hold the reference time for timeout
typedef struct {
    struct timespec reference_time;
} TimeoutManager;

// Function to set the timeout period (in milliseconds) from the current time
void set_timeout(TimeoutManager *tm, int timeout_duration_ms);

// Function to check if the timeout period has elapsed
bool check_timeout(const TimeoutManager *tm);

#endif // TIMEOUT_MANAGER_H
