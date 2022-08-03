#ifndef __FUNCTION__
#define __FUNCTION__

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "global.h"
#include "./src/timer.h"
#include "./debug/Log.h"
#include "./src/mat_mult.h"
#include "./src/gauss_elim.h"
#include "./src/mat_inv.h"
#include "./src/run_info.h"

using namespace std;

void test();

void do_q1(int = -1, bool = false);

void do_q2(int = -1, bool = false);

void do_q3(int = -1, bool = false);

void print_info(std::ostream &out, std::string heading, sarray<r_info> infos);

#endif