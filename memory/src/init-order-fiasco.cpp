#include "common.h"
#include <iostream>

static int x = globalData();

int main()
{
	std::cout << x << std::endl;
	return 0;
}
