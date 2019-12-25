#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	FILE *fp = fopen(__FILE__, "rb");
	do
	{
		if (!fp)
			break;

		if (fseek(fp, 0, SEEK_END) == -1)
			break;

		long lSize = ftell(fp);
		rewind(fp);
		if (lSize == 0)
			break;

		char *buffer = new char[lSize];
		fread(buffer, lSize, 1, fp);

		std::string str(buffer);
		delete [] buffer;
	}
	while (0);

	if (fp)
		fclose(fp);

	return 0;
}
