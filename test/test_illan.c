#include <string.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
	srand(time(0));
	char *p = malloc(100); strcpy(p, "salut les potes");
	free(p);
	realloc(p, 150);
	p = malloc(1000); strcpy(p, "salut les potes");
	free(p);
	realloc(p, 1500);
	p = malloc(1000); strcpy(p, "salut les potes");
	free(p);
	realloc(p, 1500);
	p = malloc(100); strcpy(p, "salut les potes");
	free(p);
	realloc(p, 150);
	p = malloc(100); strcpy(p, "salut les potes");
	free(p);
	realloc(p, 150);
	int i = 0;
	for (; i < 100000; ++i)
	{
		p = malloc(rand() % 100); strcpy(p, "salut les potes");
		free(p);
		realloc(p, rand() % 200);
	}
	return (0);
}
