#include <iostream>

class Foo
{
public:
	Foo()
	{

	}

	~Foo()
	{
		std::cout << "~Foo" << std::endl;
	}

	virtual void bar() const = 0;
};

class Bar : public Foo
{
public:
	Bar()
	{
		m_bar = new int[10];
	}

	~Bar()
	{
		delete [] m_bar;
		std::cout << "~Bar" << std::endl;
	}

	void bar() const override
	{
	}

private:
	int* m_bar;
};

static void no_free()
{
	int *p = new int;
}

static void new_delete_mismatch()
{
	int *p = new int[10];
	delete p;
}

static void delete_no_virtual()
{
	Foo* bar = new Bar();
	delete bar;
}

static void delete_incomplete()
{
	void* bar = new Bar();
	delete bar;
}

enum
{
	NoFree = 0,
	Mismatch,
	NoVirtual,
	Incomplete,
};

int main(int argc, char **argv)
{
	int test = NoFree;

	if (argc == 2 && argv[1])
		test = atoi(argv[1]);

	switch (test)
	{
	case Mismatch:
		new_delete_mismatch();
		break;

	case NoVirtual:
		delete_no_virtual();
		break;

	case Incomplete:
		delete_incomplete();
		break;

	case NoFree:
	default:
		no_free();
		break;
	}

	return 0;
}
