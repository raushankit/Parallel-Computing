#ifndef __MATRIX_MULT__
#define __MATRIX_MULT__

#include <iostream>
#include <fstream>
#include "timer.h"
#include "mult_args.h"
#include <omp.h>
#include <pthread.h>
#include "../include/smatrix.h"
using namespace std;

void multiply();

smatrix<int> serial_multiplication(bool = false);

pair<int64_t, int64_t> openmp_multiplication(bool = false);

pair<int64_t, int64_t> pthread_multiplication(bool = false);

void *pth_worker(void *);

void read_multiplication_input(int);

void free_memory_q1();

void print_ans(string, string);

#endif