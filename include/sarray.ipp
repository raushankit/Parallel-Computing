#include "sarray.h"

template <typename T>
_Log sarray<T>::Log = _Log("Array");

template <typename T>
sarray<T>::sarray() : n(0), arr(nullptr)
{
    Log.d("empty constructor");
}

template <typename T>
sarray<T>::sarray(const size_t _n) : n(_n), arr(new T[_n])
{
    Log.d("constructor", _n);
}

template <typename T>
sarray<T>::sarray(const sarray &_p) : n(_p.n), arr(new T[_p.n])
{
    Log.d("Copy constructor");
    std::copy(_p.arr, _p.arr + _p.n, arr);
}

template <typename T>
sarray<T>::sarray(sarray &&_p) : n(0), arr(nullptr)
{
    Log.d("move constructor");
    *this = std::move(_p);
}

template <typename T>
sarray<T> &sarray<T>::operator=(const sarray &p)
{
    Log.d("copy assignment operator");
    if (this != &p)
    {
        if (arr != nullptr)
            delete[] arr;
        n = p.n;
        arr = new T[n];
        std::copy(p.arr, p.arr + p.n, arr);
    }
    return *this;
}

template <typename T>
sarray<T> &sarray<T>::operator=(sarray &&_p)
{
    Log.d("move assignment operator");
    if (this != &_p)
    {
        n = _p.n;
        arr = _p.arr;
        _p.n = 0;
        _p.arr = nullptr;
    }
    return *this;
}

template <typename T>
sarray<T>::~sarray()
{
    Log.d("destructor");
    if (arr != nullptr)
        delete[] arr;
}

template <typename T>
T sarray<T>::diff(const sarray<T> &p) const
{
    T _diff = T(0);
    fs(i, 0, n) _diff += std::abs(arr[i] - p.arr[i]);
    if constexpr (std::is_floating_point_v<T>)
    {
        if (std::abs(_diff) <= TOLERANCE)
            _diff = T(0);
    }
    Log.i(_diff == T(0) ? "DIFF==0::Correct Answer" : "DIFF!=0::Incorrect Answer");
    return _diff;
}

template <typename T>
T &sarray<T>::operator[](size_t _n) { return arr[_n]; }

template <typename T>
const T &sarray<T>::operator[](const size_t _n) const { return arr[_n]; }

template <typename T>
std::ostream &operator<<(std::ostream &out, const sarray<T> &p)
{
    if (p.n == 0)
        return out;
    uint i = 0;
    for (uint i = 0; i < p.n - 1; ++i)
    {
        out << p.arr[i] << (std::is_class<T>::value ? '\n' : ' ');
    }
    if (i < p.n)
        out << p.arr[p.n - 1];
    return out;
}

template <typename T>
void sarray<T>::set(const T _val)
{
    std::fill(arr, arr + n, _val);
}

template <typename T>
std::istream &operator>>(std::istream &in, sarray<T> &p)
{
    fs(i, 0, p.n) in >> p.arr[i];
    return in;
}