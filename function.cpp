#include "function.h"

namespace Function
{
    _Log Log = _Log("function.h");
    timer _timer = timer(timer::Precision::MILLISECOND);
    const int fq1[] = {5, 10, 20, 50, 100, 200, 300, 500, 800, 1000};
    const int fq2[] = {5, 10, 20, 50, 100, 200, 300, 500, 800, 1000, 1500, 1800, 2000};
    const int fq3[] = {5, 10, 20, 30, 40, 50, 60, 80, 100, 120, 150};
}
using namespace Function;

void test()
{
}

void do_q1(int _n, bool print_output)
{
    Log.i("STARTING QUESTION 1");
    int max_arg = 10;
    if (_n < -1 || _n >= max_arg)
    {
        Log.w("bad argument", _n);
    }
    else if (_n == -1)
    {
        vector<r_info> info_list;
        for (int i = 0; i < max_arg; ++i)
        {
            r_info info;
            read_multiplication_input(i);
            info.n = fq1[i];
            auto o = openmp_multiplication(print_output);
            info.omp_time = o.first;
            auto p = pthread_multiplication(print_output);
            info.pthread_time = p.first;
            info.serial_time = p.second;
            info_list.push_back(info);
            cout << endl;
        }
        ofstream fout;
        fout.open("./tests/output/time/q1.txt");
        fout << "[n => serial,openmp,pthread]\n";
        for (auto __i : info_list)
            fout << __i << endl;
        fout.close();
        free_memory();
    }
    else
    {
        r_info info;
        read_multiplication_input(_n);
        info.n = fq1[_n];
        auto o = openmp_multiplication(print_output);
        info.omp_time = o.first;
        auto p = pthread_multiplication(print_output);
        info.pthread_time = p.first;
        info.serial_time = p.second;
        cout << info << endl;
        free_memory();
    }
    Log.i("ENDING QUESTION 1");
    cout << "\n**************************************************************\n";
}

void do_q2(int _n, bool print_output)
{
    Log.i("STARTING QUESTION 2");
    int max_arg = 13;
    if (_n < -1 || _n > max_arg)
    {
        Log.w("bad argument", _n);
    }
    else if (_n == -1)
    {
        vector<r_info> info_list;
        for (int i = 0; i < max_arg; ++i)
        {
            r_info info;
            info.n = fq2[i];
            auto o = omp_gauss_elim(i, print_output);
            info.omp_time = o.first;
            auto p = pthread_gauss_elim(i, print_output);
            info.pthread_time = p.first;
            info.serial_time = p.second;
            info_list.push_back(info);
            cout << endl;
        }
        ofstream fout;
        fout.open("./tests/output/time/q2.txt");
        fout << "[n => serial,openmp,pthread]\n";
        for (auto __i : info_list)
            fout << __i << endl;
        fout.close();
        free_memory_q2();
    }
    else
    {
        r_info info;
        auto o = omp_gauss_elim(_n, print_output);
        info.omp_time = o.first;
        auto p = pthread_gauss_elim(_n, print_output);
        info.pthread_time = p.first;
        info.serial_time = p.second;
        cout << info << endl;
    }
    Log.i("ENDING QUESTION 2");
    cout << "\n**************************************************************\n";
}

void do_q3(int _n, bool print_output)
{
    Log.i("STARTING QUESTION 3");
    int max_arg = 11;
    if (_n < -1 || _n > max_arg)
    {
        Log.w("bad argument", _n);
    }
    else if (_n == -1)
    {
        vector<r_info> info_list;
        for (int i = 0; i < max_arg; ++i)
        {
            r_info info;
            info.n = fq3[i];
            auto o = omp_mat_inverse_solver(i, print_output);
            info.omp_time = o.first;
            auto p = pth_mat_inverse_solver(i, print_output);
            info.pthread_time = p.first;
            info.serial_time = p.second;
            info_list.push_back(info);
            cout << endl;
        }
        ofstream fout;
        fout.open("./tests/output/time/q3.txt");
        fout << "[n => serial,openmp,pthread]\n";
        for (auto __i : info_list)
            fout << __i << endl;
        fout.close();
        free_memory_q3();
    }
    else
    {
        r_info info;
        auto o = omp_mat_inverse_solver(_n, print_output);
        info.omp_time = o.first;
        auto p = pth_mat_inverse_solver(_n, print_output);
        info.pthread_time = p.first;
        info.serial_time = p.second;
        cout << info << endl;
    }
    Log.i("ENDING QUESTION 3");
    cout << "\n**************************************************************\n";
}
