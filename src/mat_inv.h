#ifndef __MAT_INV__
#define __MAT_INV__
#include <iostream>
#include <fstream>
#include <omp.h>
#include <pthread.h>
#include "../global.h"
#include "../include/smatrix.h"
#include "../debug/Log.h"
#include "timer.h"
#include "mat_inv_args.h"
#include "mat_inv_ret.h"
using namespace std;

void read_input(int = 0);

int pivot_conditioning(int[], Matld &, int);

long double get_determinant(int, int);

sarray<long double> serial_mat_inverse_solver(int, bool = false);

pair<int64_t, int64_t> omp_mat_inverse_solver(int, bool = false);

pair<int64_t, int64_t> pth_mat_inverse_solver(int, bool = false);

sarray<long double> find_solution();

sarray<long double> omp_find_solution();

sarray<long double> pth_find_solution();

void *pth_cofactors(void *);

void *pth_mat_vect(void *);

void print_mat_inv_output(string, int, sarray<long double>);

void free_memory_q3();

#endif