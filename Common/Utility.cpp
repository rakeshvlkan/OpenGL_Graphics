#include "Utility.h"

float RandomFloat()
{
	float Max = RAND_MAX;
	return ((float)rand() / Max);
};

template <typename T> 
std::string tostr(const T& t)
{
	std::ostringstream os;
	os << t;
	return os.str();
};
