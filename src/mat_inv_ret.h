#ifndef __MAT_INV_RET__
#define __MAT_INV_RET__

#include <iostream>
#include "../include/sarray.h"

typedef struct mat_inv_ret
{
    int n;
    int start;
    int end;
    sarray<long double> _vals;

    void set(int, int, int);
    friend std::ostream &operator<<(std::ostream &, const mat_inv_ret &);
} mi_ret;

#endif