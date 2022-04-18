#include "mult_args.h"

mult_args::mult_args(int _a, int _b, int _c) : t_id(_a), start(_b), end(_c) {}

std::ostream &operator<<(std::ostream &out, const mult_args &_p)
{
    out << "thread_id = " << _p.t_id << " start = " << _p.start << " end = " << _p.end;
    return out;
}