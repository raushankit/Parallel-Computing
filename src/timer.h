#ifndef __TIMER__
#define __TIMER__

/**
 * @file timer.h
 * @author Ankit Raushan (@raushankit)
 * @brief wrapper on chrono for easy access
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

class timer
{
public:
    enum class Precision
    {
        SECOND,
        MILLISECOND,
        MICROSECOND,
        NANOSECOND
    };

    timer(Precision = Precision::NANOSECOND);
    void pin();
    int64_t get_duration(bool = false);

    int64_t print_and_update(std::string = "");

    std::string time_unit;

private:
    Precision _precision;
    std::chrono::_V2::system_clock::time_point _point;

    void change_time_unit(Precision);
};

#endif