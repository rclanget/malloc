/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:36:16 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/22 20:25:50 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>

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
	t_block *block;

	if (size > (size_t)SMALL_SIZE)
	{
		block = ft_get_new_block(LARGE, size);
		if (block)
			return ((void *)(char *)block + sizeof(t_block));	
	}
	else if (size > (size_t)TINY_SIZE)
	{
		block = ft_malloc_page(SMALL, size);
		if (block)
			return ((void *)(char *)block + sizeof(t_block));
	}
	else
	{
		block = ft_malloc_page(TINY, size);
		if (block)
			return ((void *)(char *)block + sizeof(t_block));
	}
	return (NULL);
}

void *malloc(size_t size)
{
	void *ptr;

	pthread_mutex_lock(&mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&mutex);
	return (ptr);
}