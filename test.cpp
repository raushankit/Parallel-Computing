#include "test.h"
using namespace std;

_test::_test() {}

void _test::create_tests()
{
    Log.i("checking test directories....................");
    bool _rooti = filesystem::create_directories("tests/input");
    bool _rooto = filesystem::create_directory("tests/output");
    Log.i((_rooti || _rooto) ? "[test] directories created" : "[test] directories exist");
    bool _rooti_q1 = filesystem::create_directory("tests/input/multiply");
    filesystem::create_directories("tests/input/multiply/serial");
    filesystem::create_directory("tests/input/multiply/openmp");
    filesystem::create_directory("tests/input/multiply/pthread");
    if (_rooti_q1)
    {
        generate_multiplication_tests();
    }

    bool _rooti_q2 = filesystem::create_directory("tests/input/gauss_elim");
    filesystem::create_directories("tests/output/gauss_elim/serial");
    filesystem::create_directory("tests/output/gauss_elim/openmp");
    filesystem::create_directory("tests/output/gauss_elim/pthread");
    if (_rooti_q2)
    {
        generate_gauss_elim_tests();
    }
    bool _rooti_q3 = filesystem::create_directory("tests/input/mat_inv");
    filesystem::create_directories("tests/output/mat_inv/serial");
    filesystem::create_directory("tests/output/mat_inv/openmp");
    filesystem::create_directory("tests/output/mat_inv/pthread");
    if (_rooti_q3)
    {
        generate_mat_inv_tests();
    }
    filesystem::create_directory("tests/output/time");
}

void _test::create_test_directories()
{
    bool _p = filesystem::create_directories("testing/a/b/d");
    cout << "_p = " << _p << endl;
    _p = filesystem::create_directory("testing/a/b");
    cout << "_p = " << _p << endl;
}

void _test::create_directories()
{
    create_test_directories();
}

void _test::generate_multiplication_tests()
{
    Log.i("generating test matrices for multiplication");
    auto _generate = [](int m1, int n1, int m2, int n2)
    {
        string fname = ".tests/input/multiply/";
        fname += "inp" + to_string(m1) + "x" + to_string(n1) + "_" + to_string(m2) + "x" + to_string(n2) + ".txt";
        ofstream fout(&fname[0]);
        smatrix<int> s1(m1, n1), s2(m2, n2);
        s1.fill_random(), s2.fill_random();
        fout << m1 << ' ' << n1 << '\n'
             << s1 << endl;
        fout << m2 << ' ' << n2 << '\n'
             << s2 << endl;
        Log.i("created matrices {" + to_string(m1) + "x" + to_string(n1) + "} and {" + to_string(m2) + "x" + to_string(n2) + "}");
    };

    _generate(3, 5, 5, 9);
    _generate(8, 10, 10, 12);
    _generate(20, 20, 20, 21);
    _generate(50, 55, 55, 64);
    _generate(100, 100, 100, 100);
    _generate(200, 200, 200, 200);
    _generate(300, 350, 350, 300);
    _generate(500, 500, 500, 500);
    _generate(800, 800, 800, 800);
    _generate(1000, 1000, 1000, 1000);
    Log.i("Matrices for [Question 1] generated SUCCESSFULLY!!!");
}

void _test::generate_gauss_elim_tests()
{
    Log.i("generating test matrices for gauss elimination");
    auto _generate = [](int n)
    {
        smatrix<double> _ta(n + 1, n);
        _ta.fill_random();
        string fname = "tests/input/gauss_elim/" + to_string(n) + ".txt";
        ofstream fout(&fname[0]);
        fout << n << '\n'
             << _ta;
        Log.i("created matrix {" + to_string(n) + "x" + to_string(n) + "}");
    };
    _generate(5);
    _generate(10);
    _generate(20);
    _generate(50);
    _generate(100);
    _generate(200);
    _generate(300);
    _generate(500);
    _generate(800);
    _generate(1000);
    _generate(1500);
    _generate(1800);
    _generate(2000);
    Log.i("Matrices for [Question 2] generated SUCCESSFULLY!!!");
}

void _test::generate_mat_inv_tests()
{
    Log.i("generating test matrices for matrix inversion");
    auto _generate = [](int n)
    {
        smatrix<double> _ta(n + 1, n);
        _ta.fill_random();
        string fname = "tests/input/mat_inv/" + to_string(n) + ".txt";
        ofstream fout(&fname[0]);
        fout << n << '\n'
             << _ta;
        Log.i("created matrix {" + to_string(n) + "x" + to_string(n) + "}");
    };
    _generate(5);
    _generate(10);
    _generate(20);
    _generate(30);
    _generate(40);
    _generate(50);
    _generate(60);
    _generate(80);
    _generate(100);
    _generate(120);
    _generate(150);
    Log.i("Matrices for [Question 3] generated SUCCESSFULLY!!!");
}