/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 01:36:41 by zipo              #+#    #+#             */
/*   Updated: 2017/01/24 23:04:54 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*realloc(void *ptr, size_t size)
{
	t_block		*block;
	t_block		*tmp;

	if (ptr == 0)
		return (malloc(size));
	if (!size)
		free(ptr);
	pthread_mutex_lock(&g_malloc_lock);
	if (check_adress(ptr) && (block = (t_block *)(ptr - sizeof(t_block))))
	{
		if (block->size < size && (tmp = malloc(size)))
		{
			ft_memcpy(tmp, ((void *)block + sizeof(t_block)), block->size);
			free(((void *)block + sizeof(t_block)));
			block = ((void *)tmp - sizeof(t_block));
		}
		pthread_mutex_unlock(&g_malloc_lock);
		return ((void *)block + sizeof(t_block));
	}
	pthread_mutex_unlock(&g_malloc_lock);
	return (0);
}
