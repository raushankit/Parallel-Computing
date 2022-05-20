#ifndef __CREATE_TESTS__
#define __CREATE_TESTS__

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "./include/smatrix.h"
#include "./src/timer.h"
#include "./debug/Log.h"

class _test
{
public:
    _test();
    void create_tests();

private:
    inline static timer _timer = timer(timer::Precision::MILLISECOND);
    inline static _Log Log = _Log("test.h");

    void create_directories();
    void create_test_directories();
    void generate_multiplication_tests();
    void generate_gauss_elim_tests();
    void generate_mat_inv_tests();
    void create_index(std::string path, std::vector<std::pair<int, std::string>>);
};

#endif