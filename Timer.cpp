//
// Created by kaclu on 4/4/2023.
//

#include "Timer.h"

Timer::Timer() {
    time(&lastTime);
}

double Timer::getDelta() const {
    time_t now;
    time(&now);
    return difftime(lastTime, now);
}

double Timer::lap() {
    time_t now;
    time(&now);
    double delta = difftime(lastTime, now);
    time(&lastTime);
    return delta;
}
