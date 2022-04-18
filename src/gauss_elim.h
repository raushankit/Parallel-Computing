#ifndef __GAUSS_ELIM__
#define __GAUSS_ELIM__

#include <iostream>
#include <fstream>
#include <omp.h>
#include <pthread.h>
#include "../include/smatrix.h"
#include "../debug/Log.h"
#include "gauss_elim_args.h"
#include "mult_args.h"
#include "timer.h"
using namespace std;

void read_gauss_input(int);

pair<int64_t, int64_t> omp_gauss_elim(int, bool = false);

pair<int64_t, int64_t> pthread_gauss_elim(int, bool = false);

void serial_gauss_elim(int, bool = false);

void back_substitution();

void *pth_gauss_worker(void *);

void condition_pivot(int, int);

void *parallel_worker_gauss(void *);

void print_gauss_elim_output(string, int);

void free_memory_q2();

#endif