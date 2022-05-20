#ifndef __SARRAY__
#define __SARRAY__

/**
 * @file sarray.h
 * @author Ankit Raushan (@raushankit)
 * @brief mimics vector
 * @date 2021-04-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <type_traits>
#include "../debug/Log.h"
#define f(i, k, n) for (int i = k; i < n; ++i)
#define fs(i, k, n) for (size_t i = k; i < n; ++i)

template <typename T>
class sarray
{
private:
    static _Log Log;
    inline static const double TOLERANCE = 1e-15;

public:
    sarray();
    sarray(const size_t);
    sarray(const sarray &);
    sarray(sarray &&);
    sarray &operator=(const sarray &);
    sarray &operator=(sarray &&);
    virtual ~sarray();
    T diff(const sarray &) const;
    void set(const T);
    size_t size();

    T &operator[](size_t);
    const T &operator[](const size_t) const;

    template <typename S>
    friend std::ostream &operator<<(std::ostream &, const sarray<S> &);
    template <typename S>
    friend std::istream &operator>>(std::istream &, sarray<S> &);

protected:
    size_t n;
    T *arr;
};

#include "sarray.ipp"
#endif