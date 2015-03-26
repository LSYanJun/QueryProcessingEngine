#include <stdio.h>

void readFile()
{
	FILE *fp;
	if (fp = fopen("inputQuery.txt", "wb"))
		printf("%s", "Open success\n");
	else
		printf("%s", "Open fail\n");
}
int main()
{
	readFile();
	return 0;
}