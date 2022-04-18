#include "gauss_elim_args.h"

std::ostream &operator<<(std::ostream &out, const gauss_elim_args &p)
{
    out << "tid = " << p.thread_id << " => [" << p.start << ',' << p.end << "] n = " << p.n;
    return out;
}