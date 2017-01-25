#include "tinytest.h"
#include "malloc.h"

void	reset_struct()
{
	g_main_struct = NULL;
}

void	test_init_main_struct(void)
{
	init_main_struct();
	ASSERT_EQUALS(1, (
		g_main_struct->init &&
		!g_main_struct->page &&
		!g_main_struct->free_block));
	reset_struct();
}

void	test_get_malloc_type(void)
{
	init_main_struct();
	ASSERT_EQUALS(TINY, get_malloc_type(TINY_SIZE));
	ASSERT_EQUALS(TINY, get_malloc_type(1));
	ASSERT_EQUALS(SMALL, get_malloc_type(TINY_SIZE + 1));
	ASSERT_EQUALS(SMALL, get_malloc_type(SMALL_SIZE));
	ASSERT_EQUALS(LARGE, get_malloc_type(SMALL_SIZE + 1));
	ASSERT_EQUALS(0, get_malloc_type(0));
	ASSERT_EQUALS(0, get_malloc_type(-10));
	reset_struct();
}

void	test_get_free_block_in_list(void)
{
	char *s;

	init_main_struct();
	ASSERT_EQUALS(0, get_free_block_in_list(20));
	s = malloc(20);
	ASSERT_EQUALS(0, get_free_block_in_list(20));
	free(s);
	ASSERT_EQUALS(1, get_free_block_in_list(20) ? 1 : 0);
	ASSERT_EQUALS(0, get_free_block_in_list(20));
	reset_struct();
}

void	test_check_adress(void)
{
	// char *s;

	init_main_struct();
	// Vérifier s'il trouve une adresse mallocé
	// Ne doit pas trouver adresse non malloc
	// Voir avec realloc
	reset_struct();
}

/* test runner */
int main()
{
	RUN(test_init_main_struct);
	RUN(test_get_malloc_type);
	RUN(test_get_free_block_in_list);
	system("./test.py");
	return TEST_REPORT();
}
