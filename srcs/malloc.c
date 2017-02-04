/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:38:10 by zipo              #+#    #+#             */
/*   Updated: 2017/01/25 02:25:00 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>

t_main g_main_struct;

void 		init_main_struct(void)
{
	if (g_main_struct.init != 1)
		ft_bzero(&g_main_struct, sizeof(t_main));
	g_main_struct.init = 1;
}

t_size		get_malloc_type(size_t size)
{
	if (size > 0 && size <= TINY_SIZE)
		return (TINY);
	else if (size > TINY_SIZE && size <= SMALL_SIZE)
		return (SMALL);
	else if (size > SMALL_SIZE)
		return (LARGE);
	else
		return (0);
}

t_block		*get_free_block_in_list(size_t size)
{
	t_block	*tmp;

	tmp = g_main_struct.free_block;
	while (tmp)
	{
		if (tmp->size >= size)
		{
			tmp->parent_page->free_mem -= (tmp->size + sizeof(t_block));
			if (tmp->free_next)
				tmp->free_next->free_prev = tmp->free_prev;
			if (tmp->free_prev)
				tmp->free_prev->free_next = tmp->free_next;
			else
				g_main_struct.free_block = tmp->free_next;
			tmp->free_next = 0;
			tmp->free_prev = 0;
			tmp->is_free = 0;
			break ;
		}
		tmp = tmp->free_next;
	}
	return (tmp);
}

t_block	*get_free_block(t_size type, size_t size)
{
	t_block	*block;
	t_page	*p;

	block = NULL;
	p = g_main_struct.page;
	if (!(block = get_free_block_in_list(size)))
	{
		while (p)
		{
			if ((p->type == type) && p->free_mem >= (size + sizeof(t_block)))
				break ;
			p = p->next;
		}
		if (p)
			block = insert_block_in_page(p, size);
	}
	return (block);
}

void	*malloc(size_t size)
{
	t_block	*block;
	t_size	malloc_type;

	init_main_struct();
	if ((malloc_type = get_malloc_type(size)))
	{
		pthread_mutex_lock(&g_malloc_lock);
		if ((size > SMALL_SIZE) || !(block = get_free_block(malloc_type, size)))
		{
			if (!(block = get_new_block(size)))
			{
				pthread_mutex_unlock(&g_malloc_lock);
				return (0);
			}
		}
		pthread_mutex_unlock(&g_malloc_lock);
		return ((void*)(block) + sizeof(t_block));
	}
	return (0);
}
