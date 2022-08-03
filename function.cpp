#include "function.h"

namespace Function
{
    _Log Log = _Log("function.h");
    global *_gb = global::getInstance();
}
using namespace Function;

void test()
{
}

void do_q1(int _n, bool print_output)
{
    Log.i("STARTING QUESTION 1");
    int max_arg = _gb->num_q1.size();
    if (_n < -1 || _n == 0 || _n > max_arg)
    {
        Log.w("bad argument", _n);
    }
    else if (_n == -1)
    {
        sarray<r_info> info_list(max_arg);
        for (int i = 0; i < max_arg; ++i)
        {
            Log.i("Running test case::" + to_string(i + 1) + "............");
            r_info info;
            read_multiplication_input(i);
            info.n = _gb->num_q1[i];
            auto o = openmp_multiplication(print_output);
            info.omp_time = o.first;
            auto p = pthread_multiplication(print_output);
            info.pthread_time = p.first;
            info.serial_time = p.second;
            info_list[i] = info;
            cout << endl;
        }
        ofstream fout;
        fout.open("./tests/output/time/q1.txt");
        fout << "| " << std::setw(8) << "size"
             << " || " << std::setw(15) << "serial time"
             << " | " << std::setw(15) << "openMP time "
             << " | " << std::setw(15) << "pthread time"
             << " |\n";
        fout << info_list << endl;
        fout.close();
        free_memory_q1();
    }
    else
    {
        Log.i("Running test case::" + to_string(_n) + "............");
        r_info info;
        read_multiplication_input(_n - 1);
        info.n = _gb->num_q1[_n - 1];
        auto o = openmp_multiplication(print_output);
        info.omp_time = o.first;
        auto p = pthread_multiplication(print_output);
        info.pthread_time = p.first;
        info.serial_time = p.second;
        cout << info << endl;
        free_memory_q1();
    }
    Log.i("ENDING QUESTION 1");
    cout << "**************************************************************\n";
}

void do_q2(int _n, bool print_output)
{
    Log.i("STARTING QUESTION 2");
    int max_arg = _gb->num_q2.size();
    if (_n < -1 || _n == 0 || _n > max_arg)
    {
        Log.w("bad argument", _n);
    }
    else if (_n == -1)
    {
        sarray<r_info> info_list(max_arg);
        for (int i = 0; i < max_arg; ++i)
        {
            Log.i("Running test case::" + to_string(i + 1) + "............");
            r_info info;
            info.n = _gb->num_q2[i];
            auto o = omp_gauss_elim(i, print_output);
            info.omp_time = o.first;
            auto p = pthread_gauss_elim(i, print_output);
            info.pthread_time = p.first;
            info.serial_time = p.second;
            info_list[i] = info;
            cout << endl;
        }
        ofstream fout;
        fout.open("./tests/output/time/q2.txt");
        fout << "[n => serial,openmp,pthread]\n";
        fout << info_list << endl;
        fout.close();
        free_memory_q2();
    }
    else
    {
        Log.i("Running test case::" + to_string(_n) + "............");
        r_info info;
        info.n = _gb->num_q2[_n - 1];
        auto o = omp_gauss_elim(_n - 1, print_output);
        info.omp_time = o.first;
        auto p = pthread_gauss_elim(_n - 1, print_output);
        info.pthread_time = p.first;
        info.serial_time = p.second;
        cout << info << endl;
    }
    Log.i("ENDING QUESTION 2");
    cout << "**************************************************************\n";
}

void do_q3(int _n, bool print_output)
{
    Log.i("STARTING QUESTION 3");
    int max_arg = _gb->num_q3.size();
    if (_n < -1 || _n == 0 || _n > max_arg)
    {
        Log.w("bad argument", _n);
    }
    else if (_n == -1)
    {
        sarray<r_info> info_list(max_arg);
        for (int i = 0; i < max_arg; ++i)
        {
            Log.i("Running test case::" + to_string(i + 1) + "............");
            r_info info;
            info.n = _gb->num_q3[i];
            auto o = omp_mat_inverse_solver(i, print_output);
            info.omp_time = o.first;
            auto p = pth_mat_inverse_solver(i, print_output);
            info.pthread_time = p.first;
            info.serial_time = p.second;
            info_list[i] = info;
            cout << endl;
        }
        ofstream fout;
        fout.open("./tests/output/time/q3.txt");
        fout << "[n => serial,openmp,pthread]\n";
        fout << info_list << endl;
        fout.close();
        free_memory_q3();
    }
    else
    {
        Log.i("Running test case::" + to_string(_n) + "............");
        r_info info;
        info.n = _gb->num_q3[_n - 1];
        auto o = omp_mat_inverse_solver(_n - 1, print_output);
        info.omp_time = o.first;
        auto p = pth_mat_inverse_solver(_n - 1, print_output);
        info.pthread_time = p.first;
        info.serial_time = p.second;
        cout << info << endl;
    }
    Log.i("ENDING QUESTION 3");
    cout << "**************************************************************\n";
}

void print_info(std::ostream &out, std::string heading, sarray<r_info> infos)
{
    int N_COL = 4;
    int width[N_COL] = {0};
    std::string COL_HEADERS[] = {"size of matrix", "serial execution time", "openMP execution time", "pthread execution time"};
    for (int i = 0; i < N_COL; ++i)
    {
        width[i] = 2 + COL_HEADERS[i].length();
    }
    for (int i = 0; i < (int)infos.size(); ++i)
    {
        width[0] = std::max(width[0], 1 + 2 * (int)std::to_string(infos[i].n).length());
    }
    for (int i = 0; i < (int)infos.size(); ++i)
    {
        width[1] = std::max(width[1], 2 + (int)std::to_string(infos[i].serial_time).length());
    }
    for (int i = 0; i < (int)infos.size(); ++i)
    {
        width[2] = std::max(width[2], 2 + (int)std::to_string(infos[i].omp_time).length());
    }
    for (int i = 0; i < (int)infos.size(); ++i)
    {
        width[3] = std::max(width[3], 2 + (int)std::to_string(infos[i].pthread_time).length());
    }
}
