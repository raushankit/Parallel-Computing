#ifndef __DEBUG_LOG__
#define __DEBUG_LOG__
#include <iostream>
#include <fstream>

/**
 * @file Log.h
 * @author Ankit Raushan (@raushankit)
 * @brief logging header
 * @date 2022-03-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifdef D_LEVEL1
const int _level = 1;
#elif D_LEVEL2
const int _level = 2;
#elif D_LEVEL3
const int _level = 3;
#elif D_LEVEL4
const int _level = 4;
#elif D_LEVEL5
const int _level = 5;
#else
const int _level = 6;
#endif

class _Log
{
public:
    inline _Log(std::string, bool = false);

    template <typename... Args>
    void v(Args &&...args);

    template <typename... Args>
    void d(Args &&...args);

    template <typename... Args>
    void i(Args &&...args);

    template <typename... Args>
    void w(Args &&...args);

    template <typename... Args>
    void e(Args &&...args);

private:
    std::string className = "";
    bool flag = false;
    std::ofstream fout;

    template <typename... Args>
    void print(std::string, Args &&...args);
};
#include "Log.tpp"
#endif