#include "gauss_elim.h"

namespace Solution2
{
    global *_gb = global::getInstance();
    timer _timer = timer(_gb->_time_unit);
    const int NUM_THREADS = 10;
    int64_t _stime;
    Matd a;
    sarray<double> b;
    sarray<int> id;
    const double TOL = 1e-10;
    pthread_mutex_t pivot_mutex;
    pthread_cond_t cd;
    int WORKING_THREADS;
    int count_threads = 0;
    int interval_pointer = 0;
    int thread_end[NUM_THREADS] = {0};
    pair<int, int> thread_range[NUM_THREADS];
}
using namespace Solution2;

void read_gauss_input(int _n)
{
    string name = "./tests/input/gauss_elim/";
    name = name + _gb->files_q2[_n];
    cout << name << endl;
    ifstream fin(&name[0]);
    int n;
    fin >> n;
    a = Matd(n);
    b = sarray<double>(n);
    fin >> a >> b;
    id = sarray<int>(a.n);
    fs(i, 0, a.n) id[i] = i;
}

void print_gauss_elim_output(string type, int _n)
{
    string name = "./tests/output/gauss_elim/" + type + "/" + _gb->files_q2[_n];
    ofstream fout;
    fout.open(name);
    fout << b << endl;
    fout.close();
}

void condition_pivot(int _r, int _n)
{

    if (abs(a[id[_r]][_r]) > TOL)
    {
        return;
    }
    f(j, _r + 1, _n)
    {
        if (abs(a[id[j]][_r]) > TOL)
        {
            id[j] = _r;
            id[_r] = j;
            break;
        }
        if (j == _n - 1)
        {
            cout << "bad set of equations" << endl;
        }
    }
}

pair<int64_t, int64_t> omp_gauss_elim(int _n, bool _pf)
{
    read_gauss_input(_n);
    _timer.pin();
    int n = a.n;
    int i, j, k;
    double fac;

    for (i = 0; i < n - 1; ++i)
    {
        condition_pivot(i, n);
#pragma omp parallel for shared(a, b) private(j, k, fac)
        for (j = i + 1; j < n; ++j)
        {
            fac = a[id[j]][i] / a[id[i]][i];
            for (k = i + 1; k < n; ++k)
            {
                a[id[j]][k] -= a[id[i]][k] * fac;
            }
            a[id[j]][i] = 0;
            b[id[j]] -= b[id[i]] * fac;
        }
    }
    back_substitution();
    auto _comp = b;
    auto _tomp = _timer.print_and_update("omp");
    if (_pf)
    {
        print_gauss_elim_output("openmp", _n);
    }
    serial_gauss_elim(_n, _pf);
    _comp.diff(b);
    return {_tomp, _stime};
}

void *parallel_worker_gauss(void *_args)
{
    auto data = (ge_args *)_args;
    int start = data->start;
    int end = data->end;
    int n = data->n;

    for (int i = 0; i < end; ++i)
    {
        pthread_mutex_lock(&pivot_mutex);
        count_threads++;
        if (i == thread_end[interval_pointer])
        {
            WORKING_THREADS--;
            interval_pointer++;
        }
        if (count_threads == WORKING_THREADS)
        {
            condition_pivot(i, n);
            count_threads = 0;
            pthread_cond_broadcast(&cd);
        }
        else
        {
            pthread_cond_wait(&cd, &pivot_mutex);
        }
        pthread_mutex_unlock(&pivot_mutex);

        for (int j = start; j < end; ++j)
            if (j > i)
            {
                double fac = a[id[j]][i] / a[id[i]][i];
                for (int k = i + 1; k < n; ++k)
                {
                    a[id[j]][k] -= a[id[i]][k] * fac;
                }
                a[id[j]][i] = 0;
                b[id[j]] -= b[id[i]] * fac;
            }
    }
    free(_args);
    return NULL;
}

void *pth_gauss_worker(void *_args)
{
    auto data = (pair<int, int> *)_args;
    int _tid = data->first;
    int n = data->second;

    for (int i = 0; i < n - 1; ++i)
    {
        pthread_mutex_lock(&pivot_mutex);
        count_threads++;
        if (count_threads == WORKING_THREADS)
        {
            condition_pivot(i, n);
            distribute_work(i + 1, n);
            count_threads = 0;
            pthread_cond_broadcast(&cd);
        }
        else
        {
            pthread_cond_wait(&cd, &pivot_mutex);
        }
        pthread_mutex_unlock(&pivot_mutex);

        for (int j = thread_range[_tid].first; j < thread_range[_tid].second; ++j)
        {
            double fac = a[id[j]][i] / a[id[i]][i];
            for (int k = i + 1; k < n; ++k)
            {
                a[id[j]][k] -= a[id[i]][k] * fac;
            }
            a[id[j]][i] = 0;
            b[id[j]] -= b[id[i]] * fac;
        }
    }
    free(_args);
    return NULL;
}

pair<int64_t, int64_t> pthread_gauss_elim(int _n, bool _pf)
{
    read_gauss_input(_n);
    pthread_t threads[NUM_THREADS];
    int start = 0, n = a.n;
    int _nth = n < NUM_THREADS ? n : NUM_THREADS;
    int _div = n < NUM_THREADS ? 1 : n / NUM_THREADS;
    int _compensate = n < NUM_THREADS ? 0 : n % NUM_THREADS;
    WORKING_THREADS = _nth;
    count_threads = 0;
    interval_pointer = 0;
    pthread_mutex_init(&pivot_mutex, NULL);
    pthread_cond_init(&cd, NULL);
    _timer.pin();
    for (int i = 0; i < _nth; ++i)
    {
        ge_args *_args = new ge_args();
        _args->start = start;
        _args->end = start += (_div + (i < _compensate));
        _args->thread_id = i;
        thread_end[i] = _args->end;
        _args->n = a.n;
        /*pair<int, int> *_args = new pair<int, int>();
        _args->first = i, _args->second = n;*/
        pthread_create(&threads[i], NULL, &parallel_worker_gauss, _args);
    }
    for (int i = 0; i < _nth; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&pivot_mutex);
    pthread_cond_destroy(&cd);
    back_substitution();
    auto _tpth = _timer.print_and_update("pthread");
    auto _comp = b;
    if (_pf)
    {
        print_gauss_elim_output("pthread", _n);
    }
    serial_gauss_elim(_n, _pf);
    _comp.diff(b);
    return {_tpth, _stime};
}

void serial_gauss_elim(int _n, bool _pf)
{
    read_gauss_input(_n);
    _timer.pin();
    int n = a.n;

    f(i, 0, n - 1)
    {
        condition_pivot(i, n);
        f(j, i + 1, n)
        {
            double fac = a[id[j]][i] / a[id[i]][i];
            f(k, i + 1, n)
            {
                a[id[j]][k] -= a[id[i]][k] * fac;
            }
            a[id[j]][i] = 0;
            b[id[j]] -= b[id[i]] * fac;
        }
    }
    back_substitution();
    _stime = _timer.print_and_update("serial");
    if (_pf)
    {
        print_gauss_elim_output("serial", _n);
    }
}

void distribute_work(int _str, int _n)
{
    int div = (_n - _str) / NUM_THREADS;
    int rem = (_n - _str) % NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        thread_range[i].first = _str;
        thread_range[i].second = _str += div + (rem-- > 0);
    }
}

void back_substitution()
{
    int n = a.n;
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = n - 1; j > i; --j)
            b[id[i]] -= b[id[j]] * a[id[i]][j];
        b[id[i]] /= a[id[i]][i];
    }
}

void free_memory_q2()
{
    a = Matd();
    b = sarray<double>();
    id = sarray<int>();
}