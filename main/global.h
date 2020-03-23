#pragma once

#define AS_TEXT(name) #name

inline bool is_equal(double a, double b, double eps = 1e-5)
{
	return std::fabs(a - b) < eps;
}