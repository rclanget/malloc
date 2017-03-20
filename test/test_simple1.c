#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	void *s;

	s = malloc(256);
	memset(s, (int)'0', 256);
	write(1, "1\n", 2);
	free(s);

	s = malloc(1024);
	memset(s, (int)'0', 1024);
	free(s);
	write(1, "2\n", 2);

	s = malloc(4096);
	memset(s, (int)'0', 4096);
	free(s);
	write(1, "3\n", 2);

	return (0);
}