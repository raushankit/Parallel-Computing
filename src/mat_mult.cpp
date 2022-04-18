#include "mat_mult.h"
namespace Solution1
{
    const std::string file_names[10] = {"3x5_5x9", "8x10_10x12", "20x20_20x21", "50x55_55x64", "100x100_100x100", "200x200_200x200", "300x350_350x300", "500x500_500x500", "800x800_800x800", "1000x1000_1000x1000"};
    timer _timer = timer(timer::Precision::MILLISECOND);
    const int NUM_THREADS = 10;
    Mati a, b, c;
    int64_t _stime;
    int __n;
}
using namespace Solution1;

void read_multiplication_input(int _n)
{
    string name = "./tests/input/multiply/inp";
    name = name + file_names[_n] + ".txt";
    __n = _n;
    cout << name << endl;
    ifstream fin(&name[0]);
    int m1, n1;
    fin >> m1 >> n1;
    a = Mati(m1, n1);
    int m2, n2;
    fin >> a >> m2 >> n2;
    b = Mati(m2, n2);
    fin >> b;
    c = Mati(m1, n2);
}

void print_ans(string type, string _name)
{
    string name = "./tests/output/multiply/" + type + "/" + _name + ".txt";
    ofstream fout;
    fout.open(name);
    fout << c << endl;
    fout.close();
}

void multiply()
{
    cout << a << endl;
    cout << b << endl;
}

pair<int64_t, int64_t> openmp_multiplication(bool _pf)
{
    size_t i, j, k;
    _timer.pin();
    c.set(0);
#pragma omp parallel for private(i, j, k) shared(a, b, c)
    for (i = 0; i < a.m; ++i)
    {
        for (j = 0; j < b.n; ++j)
        {
            c[i][j] = 0;
            for (k = 0; k < a.n; ++k)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    auto _tomp = _timer.print_and_update("omp");
    if (_pf)
    {
        print_ans("openmp", file_names[__n]);
    }
    auto _comp = serial_multiplication(_pf);
    cout << "diff = " << c.diff(_comp) << endl;
    return {_tomp, _stime};
}

void *pth_worker(void *t_args)
{
    auto _range = (pth_margs *)t_args;
    for (int i = _range->start; i < _range->end; ++i)
    {
        for (size_t j = 0; j < b.n; ++j)
        {
            int _temp_sum = 0;
            for (size_t k = 0; k < a.n; ++k)
            {
                _temp_sum += a[i][k] * b[k][j];
            }
            c[i][j] = _temp_sum;
        }
    }
    return NULL;
}

pair<int64_t, int64_t> pthread_multiplication(bool _pf)
{
    pthread_t thread[NUM_THREADS];
    pth_margs thread_args[NUM_THREADS];
    int start = 0;
    int _nth = a.m < NUM_THREADS ? a.m : NUM_THREADS;
    int _div = a.m < NUM_THREADS ? 1 : a.m / NUM_THREADS;
    int _compensate = _div > 1 ? a.m % NUM_THREADS : 0;
    _timer.pin();
    for (int i = 0; i < _nth; ++i)
    {
        thread_args[i].t_id = i;
        thread_args[i].start = start, thread_args[i].end = start += (_div + (i < _compensate));
        pthread_create(&thread[i], 0, &pth_worker, &thread_args[i]);
    }

    for (int i = 0; i < _nth; ++i)
    {
        pthread_join(thread[i], NULL);
    }
    auto _tpth = _timer.print_and_update("pthread");
    if (_pf)
    {
        print_ans("pthread", file_names[__n]);
    }
    auto _comp = serial_multiplication(_pf);
    cout << "diff = " << c.diff(_comp) << endl;
    return {_tpth, _stime};
}

smatrix<int> serial_multiplication(bool _pf)
{
    smatrix<int> _c(a.m, b.n);
    _timer.pin();
    for (size_t i = 0; i < a.m; ++i)
        for (size_t j = 0; j < b.n; ++j)
        {
            _c[i][j] = 0;
            for (size_t k = 0; k < a.n; ++k)
                _c[i][j] += a[i][k] * b[k][j];
        }
    _stime = _timer.print_and_update("serial");
    if (_pf)
    {
        string name = "./tests/output/multiply/serial/" + file_names[__n] + ".txt";
        ofstream fout;
        fout.open(name);
        fout << _c << endl;
        fout.close();
    }
    return _c;
}

void free_memory() { a = b = c = smatrix<int>(); }