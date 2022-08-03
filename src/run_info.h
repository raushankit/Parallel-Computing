#ifndef __RUN_INFO__
#define __RUN_INFO__
#include <iostream>

typedef struct run_info
{
    int n;
    int64_t pthread_time;
    int64_t omp_time;
    int64_t serial_time;

    friend std::ostream &operator<<(std::ostream &, const run_info &);
} r_info;

#endif