#include <iostream>

static void test()
{
	char *str = new char[100];

	if (str && *str)
		std::cout << "not empty" << std::endl;
	else
		std::cout << "empty" << std::endl;

	delete [] str;
}

int main()
{
	test();
	return 0;
}
