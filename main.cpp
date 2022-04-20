#include "function.h"
#include "test.h"
#include "./src/mat_mult.h"
#include "./src/gauss_elim.h"
#include "./src/mat_inv.h"
using namespace std;

int main(int argc, char **argv)
{
    _test test;
    test.create_tests();
    cout << "***********************************************************" << endl;
    try
    {
        if (argc == 1)
        {
            throw std::invalid_argument("invalid arguement:: no input arguments found");
        }
        int _qno = atoi(argv[1]);
        if (_qno < 1 || _qno > 3)
        {
            throw std::invalid_argument("invalid arguement:: first arguement must be between 1 and 3.");
        }
        if (argc == 3)
        {
            int _test_no = atoi(argv[2]);
            if (_qno == 1)
            {
                do_q1(_test_no);
            }
            else if (_qno == 2)
            {
                do_q2(_test_no);
            }
            else if (_qno == 3)
            {
                do_q3(_test_no);
            }
        }
        else
        {
            if (_qno == 1)
            {
                do_q1(-1);
            }
            else if (_qno == 2)
            {
                do_q2(-1);
            }
            else if (_qno == 3)
            {
                do_q3(-1);
            }
        }
    }
    catch (const std::invalid_argument &i_a)
    {
        cout << "invalid arguement:: " << i_a.what() << endl;
    }
    return 0;
}