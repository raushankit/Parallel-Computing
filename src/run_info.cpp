#include "run_info.h"

std::ostream &operator<<(std::ostream &out, const run_info &p)
{
    out << '[' << p.n << " => " << p.serial_time << ',' << p.omp_time << ',' << p.pthread_time << ']';
    return out;
}