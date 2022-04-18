#include "Log.h"

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
    print("v", args...);
}

template <typename... Args>
void _Log::d(Args &&...args)
{
    if (_level > 2)
        return;
    print("d", args...);
}

template <typename... Args>
void _Log::i(Args &&...args)
{
    if (_level > 3)
        return;
    print("i", args...);
}

template <typename... Args>
void _Log::w(Args &&...args)
{
    if (_level > 4)
        return;
    print("w", args...);
}

template <typename... Args>
void _Log::e(Args &&...args)
{
    if (_level > 5)
        return;
    print("e", args...);
}

template <typename... Args>
void _Log::print(std::string type, Args &&...args)
{
    int flag = 0;
    std::string exp[2] = {"Log::" + type + " [" + className + "]: ", ", "};
    if (this->flag)
        ((fout << exp[flag++ > 0] << args), ..., (fout << '\n'));
    else
        ((std::cout << exp[flag++ > 0] << args), ..., (std::cout << '\n'));
}