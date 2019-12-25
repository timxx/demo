#include <vector>

#ifndef _USING_ASAN
#  include <gperftools/heap-checker.h>
#  include <unistd.h>
#endif

static std::vector<int*> g_pointers;

class Foo
{
public:
	Foo()
	{
		int *p = new int[10];
		g_pointers.push_back(p);
	}

	void doSth(int i)
	{
		g_pointers.push_back(new int[i]);
	}
};

static void test()
{
#ifndef _USING_ASAN
	HeapLeakChecker checker(__FUNCTION__);
#endif

	Foo foo;
	for (int i = 0; i < 5; ++i)
	{
		foo.doSth(i);
	}

#ifndef _USING_ASAN
	checker.NoLeaks();
#endif
}

int main()
{
	test();

#ifndef _USING_ASAN
	usleep(10 * 1000 * 1000);
#endif

	for (int* p : g_pointers)
		delete [] p;

	return 0;
}
