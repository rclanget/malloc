#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		++i;
	return (i);
}

void p(char *str)
{
	write(1, str, ft_strlen(str));
}

#include <stdio.h>

void *ft_malloc_page(t_type type, size_t size)
{
	t_block *block;

	block = ft_get_free_block(type, size);
	if (block == NULL)
		block = ft_get_new_block(type, size);
	return (((char *)block + sizeof(t_block)));
}

void *ft_malloc(size_t size)
{
	if (size > (size_t)SMALL_SIZE)
		return ((char *)ft_get_new_block(LARGE, size) + sizeof(t_block));
	else if (size > (size_t)TINY_SIZE)
		return (ft_malloc_page(SMALL, size));
	else
		return (ft_malloc_page(TINY, size));
}

void *malloc(size_t size)
{
	void *ptr;

	// Mutex on
	ptr = ft_malloc(size);
	// Mutex off
	return (ptr);
}