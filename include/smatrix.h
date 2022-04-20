#ifndef __S_MATRIX__
#define __S_MATRIX__

/**
 * @file smatrix.h
 * @author Ankit Raushan (@raushankit)
 * @brief mimics matrix
 * @date 2021-04-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <random>
#include "sarray.h"
#include "../debug/Log.h"

template <typename T>
class smatrix;

typedef smatrix<double> Matd;
typedef smatrix<long double> Matld;
typedef smatrix<int> Mati;

template <typename T>
class smatrix
{
public:
    size_t m, n;

    smatrix();
    smatrix(const size_t);
    smatrix(const size_t, const size_t);
    smatrix(const smatrix &);
    smatrix(smatrix &&);
    ~smatrix();
    smatrix &operator=(const smatrix &);
    smatrix &operator=(smatrix &&);
    sarray<T> &operator[](size_t);
    const sarray<T> &operator[](const size_t) const;
    smatrix transpose() const;
    T diff(const smatrix &) const;

    template <typename S>
    friend std::ostream &operator<<(std::ostream &, const smatrix<S> &);
    template <typename S>
    friend std::istream &operator>>(std::istream &, smatrix<S> &);

    void fill_random();
    void set(T);

private:
    static _Log Log;
    inline static const double TOLERANCE = 1e-15;

    sarray<T> *arr;
};
#include "smatrix.ipp"
#endif