#ifndef __MULT_ARGS__
#define __MULT_ARGS__
#include <iostream>
#include <initializer_list>
typedef struct mult_args
{
    int t_id;
    int start;
    int end;

    mult_args(int = -1, int = -1, int = -1);
    friend std::ostream &operator<<(std::ostream &, const mult_args &);

} pth_margs;

#endif