
typedef unsigned long PROPVALUE;

static void test(PROPVALUE *value)
{
	if (value)
		*value = 2020;
}

int main()
{
	int n = 0;
	test((PROPVALUE*)&n);

	return 0;
}
