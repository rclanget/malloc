/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 19:00:08 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/22 19:26:11 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_fusion_block(t_block *block, size_t size)
{
	t_block	*next;
	size_t	save_size;

	save_size = block->size;
	while (block->size < size && (next = block->next) && next->free)
	{
		block->next = next->next;
		block->size += (next->size + sizeof(t_block));
	}
	if (block->size >= size)
	{
		block->parent_page->capacity -= (size - save_size);
		if (!block->next)
			block->parent_page->offset += (size - save_size);
		return ((void *)(char *)block + sizeof(t_block));
	}
	else
		return (NULL);
}

static void	*ft_realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new;
	size_t	ptr_size;

	if (!ptr || !*((char *)ptr))
		return (ft_malloc(size));
	block = (t_block *)(ptr - sizeof(t_block));
	new = NULL;
	if (block && (block->free || block->magic_1 != 0x29a))
		return (NULL);
	if (size <= (size_t)SMALL_SIZE)
	{
		if ((size > (size_t)TINY_SIZE && block->parent_page->type != TINY) || size < (size_t)TINY_SIZE)
			new = ft_fusion_block(block, size);
	}
	if (!new)
	{
		new = ft_malloc(size);
		ptr_size = block->size;
		ft_memcpy(new, ptr, ptr_size);
		ft_free(ptr);
	}
	return (new);
}

void	*reallocf(void *ptr, size_t size)
{
	void *new;

	pthread_mutex_lock(&mutex);
	new = ft_realloc(ptr, size);
	if (!new)
		ft_free(ptr);
	pthread_mutex_unlock(&mutex);
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&mutex);
	ptr = ft_realloc(ptr, size);
	pthread_mutex_unlock(&mutex);
	return (ptr);
}