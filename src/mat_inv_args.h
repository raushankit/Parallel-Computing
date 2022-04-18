#ifndef __MAT_INV_ARGS__
#define __MAT_INV_ARGS__
#include <iostream>
typedef struct mat_inv_args
{
    int thread_id;
    int n;
    int _exec_start;
    int _exec_end;

    friend std::ostream &operator<<(std::ostream &, const mat_inv_args &);
} mi_args;

#endif