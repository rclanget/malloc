#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>

#include <stdio.h>

void *ft_malloc_page(t_type type, size_t size)
{
	t_block *block;

	block = ft_get_free_block(type, size);
	if (block == NULL)
		block = ft_get_new_block(type, size);
	return (block);
}

void *ft_malloc(size_t size)
{
	if (size > (size_t)SMALL_SIZE)
		return ((char *)ft_get_new_block(LARGE, size) + sizeof(t_block));
	else if (size > (size_t)TINY_SIZE)
		return ((char *)ft_malloc_page(SMALL, size) + sizeof(t_block));
	else
		return ((char *)ft_malloc_page(TINY, size) + sizeof(t_block));
}

void *malloc(size_t size)
{
	void *ptr;

ft_print("malloc_in\n");
	pthread_mutex_lock(&mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&mutex);
ft_print("malloc_end\n");
	return (ptr);
}