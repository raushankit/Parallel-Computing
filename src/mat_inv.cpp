#include "mat_inv.h"
namespace Solution3
{
    const std::string file_names[] = {"5", "10", "20", "30", "40", "50", "60", "80", "100", "120", "150"};
    const double TOL = 1e-10;
    timer _timer = timer(timer::Precision::MICROSECOND);
    const int NUM_THREADS = 10;
    const int SIZE_THRESHOLD = 49;
    int64_t _stime;
    Matld inv, a;
    sarray<long double> b, __det;
    pthread_barrier_t barrier;
    pthread_mutex_t mutex;
}
using namespace Solution3;

void read_input(int _n)
{
    string name = "./tests/input/mat_inv/";
    name = name + file_names[_n] + ".txt";
    cout << name << endl;
    ifstream fin(&name[0]);
    int n;
    fin >> n;
    a = Matld(n);
    inv = Matld(n);
    b = sarray<long double>(n);
    fin >> a >> b;
}

void print_mat_inv_output(string type, int _n, sarray<long double> p)
{
    string name = "./tests/output/mat_inv/" + type + "/" + file_names[_n] + ".txt";
    ofstream fout;
    fout.open(name);
    fout << p << endl;
    fout.close();
}

int pivot_conditioning(int _id[], Matld &p, int _r)
{
    if (abs(p[_id[_r]][_r]) > TOL)
    {
        return -1;
    }
    int _n = p.n;
    f(j, _r + 1, _n)
    {
        if (abs(p[_id[j]][_r]) > TOL)
        {
            _id[j] = _r;
            _id[_r] = j;
            return 1;
        }
        if (j == _n - 1)
        {
            return 0;
        }
    }
    return -1;
}

long double get_determinant(int _exc_i, int _exc_j)
{
    int n = a.n;
    Matld p(n - 1);
    int _ri = 0;
    f(i, 0, n) if (i != _exc_i)
    {
        int _rj = 0;
        f(j, 0, n) if (j != _exc_j)
        {
            p[_ri][_rj++] = a[i][j];
        }
        _ri++;
    }
    n--;
    if (n == 1)
    {
        return p[0][0];
    }
    if (n == 2)
    {
        return p[0][0] * p[1][1] - p[0][1] * p[1][0];
    }
    long double det = 1.0;
    int id[n];
    int _sign = 1;
    f(i, 0, n) id[i] = i;
    f(i, 0, n - 1)
    {
        int __pc = pivot_conditioning(id, p, i);
        if (__pc == 0)
        {
            return 0;
        }
        if (__pc == 1)
            _sign *= -1;
        det *= p[id[i]][i];
        f(j, i + 1, n)
        {
            double fac = p[id[j]][i] / p[id[i]][i];
            f(k, i + 1, n)
            {
                p[id[j]][k] -= p[id[i]][k] * fac;
            }
        }
    }
    return _sign * det * p[id[n - 1]][n - 1];
}

sarray<long double> find_solution()
{
    long double det = 0;
    int n = a.n;
    f(i, 0, n) det += a[i][0] * inv[i][0];
    sarray<long double> ans(n);
    f(i, 0, n)
    {
        ans[i] = 0;
        f(j, 0, n)
        {
            ans[i] += inv[j][i] * b[j];
        }
        ans[i] /= det;
    }
    return ans;
}

sarray<long double> omp_find_solution()
{
    long double det = 0;
    int n = a.n;
    f(i, 0, n) det += a[i][0] * inv[i][0];
    sarray<long double> ans(n);
    int _i;
#pragma omp parallel for shared(ans) private(_i) if (n > SIZE_THRESHOLD)
    for (_i = 0; _i < n; ++_i)
    {
        ans[_i] = 0;
        f(j, 0, n)
        {
            ans[_i] += inv[j][_i] * b[j];
        }
        ans[_i] /= det;
    }
    return ans;
}

void *pth_cofactors(void *_args)
{
    mi_args *data = (mi_args *)_args;
    int n = data->n;
    for (int i = data->_exec_start; i < data->_exec_end; ++i)
    {
        int _ri = i / n, _rj = i % n;
        inv[_ri][_rj] = (1 - 2 * ((_ri + _rj) & 1)) * get_determinant(_ri, _rj);
    }

    pthread_barrier_wait(&barrier);
    mi_ret *_ret = new mi_ret();
    _ret->set(data->_exec_start, data->_exec_end, n);
    for (int i = _ret->start; i < _ret->end; ++i)
    {
        long double _ans = 0;
        __det[data->thread_id] += a[i][0] * inv[i][0];
        f(j, 0, n)
        {
            _ans += inv[j][i] * b[j];
        }
        _ret->_vals[i - _ret->start] = _ans;
    }
    free(_args);
    return (void *)_ret;
}

pair<int64_t, int64_t> pth_mat_inverse_solver(int _n, bool _pf)
{
    read_input(_n);
    _timer.pin();
    int n = a.n;
    int _sqn = n * n;
    int _cur = 0;
    int _nth = _sqn < NUM_THREADS ? _sqn : NUM_THREADS;
    int _div = _sqn / NUM_THREADS;
    __det = sarray<long double>(_nth);
    sarray<long double> _ans(n);
    __det.set(0);
    int _rem = _sqn % NUM_THREADS;

    pthread_t threads[_nth];
    pthread_barrier_init(&barrier, NULL, _nth);
    void *ans;
    f(i, 0, _nth)
    {
        mi_args *_args = new mi_args();
        _args->_exec_start = _cur;
        _args->_exec_end = _cur += _div + (_rem-- > 0);
        _args->thread_id = i;
        _args->n = n;
        pthread_create(&threads[i], NULL, pth_cofactors, (void *)_args);
    }
    f(i, 0, _nth)
    {
        pthread_join(threads[i], &ans);
        mi_ret *_t = (mi_ret *)ans;
        f(j, _t->start, _t->end) _ans[j] = _t->_vals[j - _t->start];
        delete _t;
    }
    pthread_barrier_destroy(&barrier);
    long double _det = 0;
    f(i, 0, _nth) _det += __det[i];
    f(i, 0, n) _ans[i] /= _det;
    auto _tpth = _timer.print_and_update("pthreads");
    if (_pf)
    {
        print_mat_inv_output("pthread", _n, _ans);
    }
    auto _x = serial_mat_inverse_solver(_n, _pf);
    _ans.diff(_x);
    return {_tpth, _stime};
}

pair<int64_t, int64_t> omp_mat_inverse_solver(int _n, bool _pf)
{
    read_input(_n);
    _timer.pin();
    int n = a.n;
    int i, j;

#pragma omp parallel for private(i, j) collapse(2)
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            inv[i][j] = ((i + j) & 1 ? -1 : 1) * get_determinant(i, j);
        }
    }
    auto _comp = omp_find_solution();
    auto _tomp = _timer.print_and_update("omp");
    if (_pf)
    {
        print_mat_inv_output("openmp", _n, _comp);
    }
    auto _x = serial_mat_inverse_solver(_n, _pf);
    _comp.diff(_x);
    return {_tomp, _stime};
}

sarray<long double> serial_mat_inverse_solver(int _n, bool _pf)
{
    read_input(_n);
    _timer.pin();
    int n = a.n;
    f(i, 0, n) f(j, 0, n)
    {
        inv[i][j] = ((i + j) & 1 ? -1 : 1) * get_determinant(i, j);
    }
    auto _ans = find_solution();
    _stime = _timer.print_and_update("serial");
    if (_pf)
    {
        print_mat_inv_output("serial", _n, _ans);
    }
    return _ans;
}

void free_memory_q3()
{
    a = Matld();
    inv = Matld();
    b = sarray<long double>();
    __det = sarray<long double>();
}