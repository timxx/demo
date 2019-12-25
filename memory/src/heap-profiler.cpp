#ifndef _USING_ASAN

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <gperftools/heap-profiler.h>

class Foo
{
public:
	Foo()
	{

	}

	void doSth()
	{
		for (int i = 0; i < 100; ++i)
		{
			m_map[i] = std::to_string(i);
		}
	}

private:
	std::map<int, std::string> m_map;
};

static void test()
{
	HeapProfilerStart(__FUNCTION__);

	Foo foo;
	foo.doSth();

	std::vector<long*> pointers;
	for (int i = 0; i < 500; ++i)
	{
		pointers.push_back(new long[i]);
	}

	for (long* p : pointers)
		delete [] p;

	HeapProfilerDump("blabla");
	HeapProfilerStop();
}

#else

#include <iostream>

static void test()
{
	std::cout << "Please pass -DENABLE_ASAN=OFF to cmake" << std::endl;
}
#endif

int main()
{
	test();

	return 0;
}
