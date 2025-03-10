#include "timeout_manager.h"

void set_timeout(TimeoutManager *tm, int timeout_duration_ms) {
    clock_gettime(CLOCK_MONOTONIC, &tm->reference_time);
    tm->reference_time.tv_sec += timeout_duration_ms / 1000;
    tm->reference_time.tv_nsec += (timeout_duration_ms % 1000) * 1000000;
    if (tm->reference_time.tv_nsec >= 1000000000) {
        tm->reference_time.tv_sec++;
        tm->reference_time.tv_nsec -= 1000000000;
    }
}

bool check_timeout(const TimeoutManager *tm) {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);

    if (current_time.tv_sec > tm->reference_time.tv_sec ||
        (current_time.tv_sec == tm->reference_time.tv_sec && current_time.tv_nsec >= tm->reference_time.tv_nsec)) {
        return true;
    } else {
        return false;
    }
}
