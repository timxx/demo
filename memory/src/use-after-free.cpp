
int main(int argc, char **argv)
{
	int *p = new int;
	delete p;
	*p = 0;

	return 0;
}
