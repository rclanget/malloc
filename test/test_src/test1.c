/* Tests for myfunctions.c, using TinyTest. */

#include "tinytest.h"
#include "malloc.h"

// #include "malloc.h"

void test_addition()
{
	char *str;

	str = NULL;
	str = (char *)malloc(8);
	ASSERT_EQUALS(1, check_adress(str));
}

/* test runner */
int main()
{
	RUN(test_addition);
	return TEST_REPORT();
}
