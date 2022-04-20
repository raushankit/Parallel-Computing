#include "smatrix.h"

template <typename T>
_Log smatrix<T>::Log = _Log("Matrix");

template <typename T>
smatrix<T>::smatrix() : m(0), n(0), arr(nullptr)
{
    Log.d("empty constructor");
}

template <typename T>
smatrix<T>::smatrix(const size_t _n) : m(_n), n(_n), arr(new sarray<T>[_n])
{
    Log.d("square matrix constructor", _n);
    std::fill(arr, arr + _n, sarray<T>(_n));
}

template <typename T>
smatrix<T>::smatrix(const size_t _m, const size_t _n) : m(_m), n(_n), arr(new sarray<T>[_m])
{
    Log.d("matrix constructor", _m, _n);
    std::fill(arr, arr + _m, sarray<T>(_n));
}

template <typename T>
smatrix<T>::smatrix(const smatrix &_p) : m(_p.m), n(_p.n), arr(new sarray<T>[_p.n])
{
    Log.d("copy constructor");
    std::copy(_p.arr, _p.arr + _p.m, arr);
}

template <typename T>
smatrix<T>::~smatrix()
{
    Log.d("destructor");
    if (arr != nullptr)
        delete[] arr;
}

template <typename T>
smatrix<T> &smatrix<T>::operator=(const smatrix<T> &_p)
{
    Log.d("copy assignment operator");
    if (this != &_p)
    {
        if (arr != nullptr)
            delete[] arr;
        m = _p.m, n = _p.n, arr = _p.arr;
        std::copy(_p.arr, _p.arr + _p.m, arr);
    }
    return *this;
}

template <typename T>
smatrix<T>::smatrix(smatrix &&_p) : m(0), n(0), arr(nullptr)
{
    Log.d("move constructor");
    *this = std::move(_p);
}

template <typename T>
smatrix<T> &smatrix<T>::operator=(smatrix<T> &&_p)
{
    Log.d("move assignment operator");
    if (this != &_p)
    {
        m = _p.m, n = _p.n, arr = _p.arr;
        _p.m = _p.n = 0;
        _p.arr = nullptr;
    }
    return *this;
}

template <typename T>
sarray<T> &smatrix<T>::operator[](size_t _i) { return arr[_i]; }

template <typename T>
const sarray<T> &smatrix<T>::operator[](const size_t _i) const { return arr[_i]; }

template <typename T>
smatrix<T> smatrix<T>::transpose() const
{
    smatrix<T> _t(n, m);
    fs(i, 0, m) fs(j, 0, n) _t[j][i] = arr[i][j];
    return _t;
}

template <typename T>
T smatrix<T>::diff(const smatrix<T> &p) const
{
    if (m != p.m || n != p.n)
        return T(0);
    T _diff = T(0);
    fs(i, 0, m) fs(j, 0, n) _diff += std::abs(arr[i][j] - p.arr[i][j]);
    if constexpr (std::is_floating_point_v<T>)
    {
        if (std::abs(_diff) <= TOLERANCE)
            _diff = T(0);
    }
    Log.i(_diff == T(0) ? "DIFF==0::Correct Answer" : "DIFF!=0::Incorrect Answer");
    return _diff;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const smatrix<T> &p)
{
    if (p.arr == nullptr)
        return out;
    fs(i, 0, p.m - 1) out << p.arr[i] << std::endl;
    if (p.m > 0)
        out << p.arr[p.m - 1];
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &in, smatrix<T> &p)
{
    fs(i, 0, p.m) in >> p.arr[i];
    return in;
}

template <typename T>
void smatrix<T>::fill_random()
{
    std::mt19937 rng;
    rng.seed(rng.default_seed);
    if constexpr (std::is_integral_v<T>)
    {
        std::uniform_int_distribution<T> unif_rand(1, std::max(m, n));
        fs(i, 0, m) fs(j, 0, n) arr[i][j] = unif_rand(rng);
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        std::uniform_real_distribution<T> unif_real(1, std::max(m, n));
        fs(i, 0, m) fs(j, 0, n) arr[i][j] = unif_real(rng);
    }
    else
    {
        Log.w("arguement neither integral not floating point");
    }
}

template <typename T>
void smatrix<T>::set(T _def)
{
    fs(i, 0, m) fs(j, 0, n) arr[i][j] = _def;
}
