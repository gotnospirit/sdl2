#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

std::string getFilepath(const char *);

int clamp(int, int, int);

float linearEaseIn(int, float, float, int);

#endif // _UTILS_H_