#ifndef __GAUSS_ELIM_ARGS__
#define __GAUSS_ELIM_ARGS__
#include <iostream>
typedef struct gauss_elim_args
{
    int start;
    int end;
    int thread_id;
    int n;

    friend std::ostream &operator<<(std::ostream &, const gauss_elim_args &);

} ge_args;

#endif