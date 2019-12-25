
__attribute__((noinline)) static const char* test()
{
	char buffer[] = "hello";
	return buffer;
}

int main(int argc, char **argv)
{
	const char* s = test();
	if (s && s[0])
	{

	}

	return 0;
}
