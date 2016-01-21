#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

std::string getFilepath(const char *);

int clamp(int, int, int);

float linearEaseIn(float, float, float, float);

#endif // _UTILS_H_