#ifndef __GLOBAL__
#define __GLOBAL__
#include <iostream>
#include <fstream>
#include "./src/timer.h"
#include "./include/sarray.h"

class global
{
public:
    std::string path_q1;
    std::string path_q2;
    std::string path_q3;

    sarray<std::string> files_q1;
    sarray<std::string> files_q2;
    sarray<std::string> files_q3;

    sarray<int> num_q1;
    sarray<int> num_q2;
    sarray<int> num_q3;

    timer::Precision _time_unit;

    static global *getInstance();

    void fetch_data();

private:
    static global *INSTANCE;

    explicit global();
    void fetch_info(std::string, sarray<int> &, sarray<std::string> &);
};

#endif