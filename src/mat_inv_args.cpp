#include "mat_inv_args.h"

std::ostream &operator<<(std::ostream &out, const mat_inv_args &p)
{
    out << "tid = " << p.thread_id << " exclude[" << p._exec_start << ',' << p._exec_end << "] n = " << p.n;
    return out;
}