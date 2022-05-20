#include "test.h"

_test::_test() {}

void _test::create_tests()
{
    Log.i("checking test directories....................");
    bool _rooti = std::filesystem::create_directories("./tests/input");
    bool _rooto = std::filesystem::create_directory("./tests/output");
    Log.i((_rooti || _rooto) ? "[test] directories created" : "[test] directories exist");
    bool _rooti_q1 = std::filesystem::create_directory("./tests/input/multiply");
    std::filesystem::create_directories("./tests/output/multiply/serial");
    std::filesystem::create_directory("./tests/output/multiply/openmp");
    std::filesystem::create_directory("./tests/output/multiply/pthread");
    if (_rooti_q1)
    {
        generate_multiplication_tests();
    }
    std::cout << std::endl;

    bool _rooti_q2 = std::filesystem::create_directory("./tests/input/gauss_elim");
    std::filesystem::create_directories("./tests/output/gauss_elim/serial");
    std::filesystem::create_directory("./tests/output/gauss_elim/openmp");
    std::filesystem::create_directory("./tests/output/gauss_elim/pthread");
    if (_rooti_q2)
    {
        generate_gauss_elim_tests();
    }
    std::cout << std::endl;
    bool _rooti_q3 = std::filesystem::create_directory("./tests/input/mat_inv");
    std::filesystem::create_directories("./tests/output/mat_inv/serial");
    std::filesystem::create_directory("./tests/output/mat_inv/openmp");
    std::filesystem::create_directory("./tests/output/mat_inv/pthread");
    if (_rooti_q3)
    {
        generate_mat_inv_tests();
    }
    std::filesystem::create_directory("./tests/output/time");
}

void _test::create_test_directories()
{
    bool _p = std::filesystem::create_directories("./testing/a/b/d");
    _p = std::filesystem::create_directory("./testing/a/b");
    Log.i(_p ? "parent directory created!!" : "parent directory exists!!");
}

void _test::create_directories()
{
    create_test_directories();
}

void _test::create_index(std::string path, std::vector<std::pair<int, std::string>> content)
{
    path += "index.txt";
    std::ofstream fout(&path[0]);
    fout << content.size() << std::endl;
    for (auto x : content)
    {
        fout << x.first << ' ' << x.second << std::endl;
    }
}

void _test::generate_multiplication_tests()
{
    Log.i("generating test matrices for multiplication");
    std::vector<std::pair<int, std::string>> index_list;
    auto _generate = [&index_list](int m1, int n1, int m2, int n2)
    {
        std::string file_name = std::to_string(m1) + "x" + std::to_string(n1) + "_" + std::to_string(m2) + "x" + std::to_string(n2) + ".txt";
        std::string fname = "./tests/input/multiply/" + file_name;
        std::ofstream fout(&fname[0]);
        smatrix<int> s1(m1, n1), s2(m2, n2);
        index_list.push_back({(m1 + m2 + n1 + n2) / 4, file_name});
        s1.fill_random(), s2.fill_random();
        fout << m1 << ' ' << n1 << '\n'
             << s1 << std::endl;
        fout << m2 << ' ' << n2 << '\n'
             << s2 << std::endl;
        Log.i("created matrices {" + std::to_string(m1) + "x" + std::to_string(n1) + "} and {" + std::to_string(m2) + "x" + std::to_string(n2) + "}");
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
    create_index("./tests/input/multiply/", index_list);
    Log.i("Matrices for [Question 1] generated SUCCESSFULLY!!!");
}

void _test::generate_gauss_elim_tests()
{
    Log.i("generating test matrices for gauss elimination");
    std::vector<std::pair<int, std::string>> index_list;
    auto _generate = [&index_list](int n)
    {
        smatrix<double> _ta(n + 1, n);
        _ta.fill_random();
        std::string fname = "./tests/input/gauss_elim/" + std::to_string(n) + ".txt";
        std::ofstream fout(&fname[0]);
        index_list.push_back({n, std::to_string(n) + ".txt"});
        fout << n << '\n'
             << _ta;
        Log.i("created matrix {" + std::to_string(n) + "x" + std::to_string(n) + "}");
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
    create_index("./tests/input/gauss_elim/", index_list);
    Log.i("Matrices for [Question 2] generated SUCCESSFULLY!!!");
}

void _test::generate_mat_inv_tests()
{
    Log.i("generating test matrices for matrix inversion");
    std::vector<std::pair<int, std::string>> index_list;
    auto _generate = [&index_list](int n)
    {
        smatrix<double> _ta(n + 1, n);
        _ta.fill_random();
        std::string fname = "./tests/input/mat_inv/" + std::to_string(n) + ".txt";
        std::ofstream fout(&fname[0]);
        index_list.push_back({n, std::to_string(n) + ".txt"});
        fout << n << '\n'
             << _ta;
        Log.i("created matrix {" + std::to_string(n) + "x" + std::to_string(n) + "}");
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
    create_index("./tests/input/mat_inv/", index_list);
    Log.i("Matrices for [Question 3] generated SUCCESSFULLY!!!");
}