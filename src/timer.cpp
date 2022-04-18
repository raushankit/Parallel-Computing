#include "timer.h"

timer::timer(Precision _precision) : _precision(_precision)
{
    change_time_unit(_precision);
}

void timer::pin() { _point = Clock::now(); }

int64_t timer::get_duration(bool flag)
{
    auto _now = Clock::now();
    switch (_precision)
    {
    case Precision::SECOND:
        return std::chrono::duration_cast<std::chrono::seconds>(_now - _point).count();
    case Precision::MILLISECOND:
        return std::chrono::duration_cast<std::chrono::milliseconds>(_now - _point).count();
    case Precision::MICROSECOND:
        return std::chrono::duration_cast<std::chrono::microseconds>(_now - _point).count();
    default:
        return std::chrono::duration_cast<std::chrono::nanoseconds>(_now - _point).count();
    }
    if (flag)
        _point = _now;
}

int64_t timer::print_and_update(std::string name)
{
    int64_t _duration = get_duration(true);
    printf("Time Taken[%s]:: %ld %s\n", &name[0], _duration, &time_unit[0]);
    return _duration;
}

void timer::change_time_unit(Precision _pre)
{
    switch (_pre)
    {
    case Precision::SECOND:
        time_unit = "seconds";
        break;
    case Precision::MILLISECOND:
        time_unit = "milliseconds";
        break;
    case Precision::MICROSECOND:
        time_unit = "microseconds";
        break;
    default:
        time_unit = "nanoseconds";
    }
}