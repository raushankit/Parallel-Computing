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
    inline static const std::string _COLOR_ARRAY[] = {"97", "36", "32", "33", "31", "39"};

    std::string className = "";
    bool flag = false;
    std::ofstream fout;

    template <typename... Args>
    void print(int type_n, std::string, Args &&...args);
};
#include "Log.tpp"
#endif