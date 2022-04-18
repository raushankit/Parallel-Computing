#include "mat_inv_ret.h"

void mat_inv_ret::set(int _str, int _end, int _n)
{
    this->start = _str / _n;
    this->end = _end / _n;
    this->n = end-start;
    this->_vals = sarray<long double>(n);
}

std::ostream &operator<<(std::ostream &out, const mat_inv_ret &p)
{
    out << "[" << p.start << ',' << p.end << "] => " << p._vals;
    return out;
}