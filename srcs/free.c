/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:42:13 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/22 20:54:03 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void ft_free(void *ptr)
{
	t_block *block;

	if (ptr && *((char *)ptr))
	{
		block = (t_block *)((void *)(char *)ptr - sizeof(t_block));
		if (block && block->magic_1 == 0x29a)
		{
			block->free = 1;
			block->parent_page->capacity += block->size;
			ft_bzero((void *)(char *)block + sizeof(t_block), block->size);
		}
	}
}

void free(void *ptr)
{
	pthread_mutex_lock(&mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&mutex);
}