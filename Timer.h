//
// Created by kaclu on 4/4/2023.
//

#ifndef MIATA_DASH_SW_TIMER_H
#define MIATA_DASH_SW_TIMER_H
#include "ctime"

class Timer {
public:
    Timer();
    [[nodiscard]] double getDelta() const;
    double lap();
private:
    time_t lastTime{};
};


#endif //MIATA_DASH_SW_TIMER_H
