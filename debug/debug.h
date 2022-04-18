#ifndef __DEBUG_GUARD__
#define __DEBUG_GUARD__
#ifdef DEBUG
/**
 * @file debug.h
 * @author Ankit Raushan (@raushankit)
 * @brief debug helper
 * @date 2022-03-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template <typename... Args>
void logger(std::string vars, Args &&...values)
{
     size_t i = 0;
     char exp[2] = {',', '\0'};
     ((
          std::cout << exp[i == 0] << [values, &i, vars]()
          {
                      std::string temp = "";
                      while(i < vars.length() && vars[i] != ',') temp += vars[i++];
                      i++;
                      return temp; }() << " = "
                    << values),
      ..., (std::cout << "\n"));
}
#elif NDEBUG
#define deb(...)
#endif
#endif