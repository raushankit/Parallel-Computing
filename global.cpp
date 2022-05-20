#include "global.h"

global::global()
{
    _time_unit = timer::Precision::MICROSECOND;

    path_q1 = "./tests/input/multiply/";
    path_q2 = "./tests/input/gauss_elim/";
    path_q3 = "./tests/input/mat_inv/";

    /*std::cout << files_q1 << "\n\n"
              << files_q2 << "\n\n"
              << files_q3 << "\n\n\n";*/
}

void global::fetch_data()
{
    fetch_info(path_q1, num_q1, files_q1);
    fetch_info(path_q2, num_q2, files_q2);
    fetch_info(path_q3, num_q3, files_q3);
}

void global::fetch_info(std::string path, sarray<int> &fn, sarray<std::string> &fs)
{
    path += "index.txt";
    std::ifstream fin(&path[0]);
    int _n = 0;
    fin >> _n;
    fn = sarray<int>(_n);
    fs = sarray<std::string>(_n);
    for (int i = 0; i < _n; ++i)
    {
        fin >> fn[i] >> fs[i];
    }
}

global *global::getInstance()
{
    if (INSTANCE == nullptr)
    {
        INSTANCE = new global;
    }
    return INSTANCE;
}