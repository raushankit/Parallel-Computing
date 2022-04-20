#include "Log.h"

#ifdef D_LEVEL1
const int _level = 1;
#elif D_LEVEL2
const int _level = 2;
#elif D_LEVEL3
const int _level = 3;
#elif D_LEVEL4
const int _level = 4;
#elif D_LEVEL5
const int _level = 5;
#else
const int _level = 6;
#endif

const std::string __RESET_TEXT_COL = "\033[0m\n";

_Log::_Log(std::string name, bool writeToFile) : className(name), flag(writeToFile)
{
    if (!flag)
        return;
    fout.open("./debug/logs/debug_" + name + ".txt", std::ios::trunc | std::ios::out);
}

template <typename... Args>
void _Log::v(Args &&...args)
{
    if (_level > 1)
        return;
    print(0, "v", args...);
}

template <typename... Args>
void _Log::d(Args &&...args)
{
    if (_level > 2)
        return;
    print(1, "d", args...);
}

template <typename... Args>
void _Log::i(Args &&...args)
{
    if (_level > 3)
        return;
    print(2, "i", args...);
}

template <typename... Args>
void _Log::w(Args &&...args)
{
    if (_level > 4)
        return;
    print(3, "w", args...);
}

template <typename... Args>
void _Log::e(Args &&...args)
{
    if (_level > 5)
        return;
    print(4, "e", args...);
}

template <typename... Args>
void _Log::print(int type_n, std::string type, Args &&...args)
{
    auto _text_col = [](int _n)
    {
        if (_n >= 2)
        {
            return "\033[1;" + _COLOR_ARRAY[_n] + ";49m";
        }
        return "\033[0;" + _COLOR_ARRAY[_n] + ";49m";
    };
    int flag = 0;
    std::string exp[2] = {"Log::" + type + " [" + className + "] ", ", "};
    if (this->flag)
        ((fout << exp[flag++ > 0] << args), ..., (fout << '\n'));
    else
        ((std::cout << _text_col(type_n) << exp[flag++ > 0] << args), ..., (std::cout << __RESET_TEXT_COL));
}