/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:38:10 by zipo              #+#    #+#             */
/*   Updated: 2017/01/23 12:52:50 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>

static void init_main_struct(void)
{
	void *buf;

	if (g_main_struct)
		return ;
	if ((buf = mmap(0, sizeof(g_main_struct), MMAP_FLAG, -1, 0)) != (void *)-1)
	{
		g_main_struct = (t_main *)buf;
		ft_bzero(g_main_struct, sizeof(t_main));
		g_main_struct->init = 1;
	}
}

t_size	get_malloc_type(size_t size)
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

t_block	*get_free_block_in_list(size_t size)
{
	t_block	*tmp;

	tmp = g_main_struct->free_block;
	int i = 0;
	while (tmp)
	{
		if (tmp->size >= size)
			break ;
		tmp = tmp->free_next;
		if (i++ > 3)
			break ;
	}
	if (tmp)
	{
		tmp->parent_page->free_mem -= (tmp->size + sizeof(t_block));
		if (tmp->free_next)
			tmp->free_next->free_prev = tmp->free_prev;
		if (tmp->free_prev)
			tmp->free_prev->free_next = tmp->free_next;
		else
			g_main_struct->free_block = tmp->free_next;
		tmp->free_next = 0;
		tmp->free_prev = 0;
		tmp->is_free = 0;
	}
	return (tmp);
}

t_block	*get_free_block(t_size type, size_t size)
{
	t_block	*block;
	t_page	*tmp;

	block = NULL;
	tmp = g_main_struct->page;
	if (!(block = get_free_block_in_list(size)))
	{
		while (tmp)
		{
			if ((tmp->type == type) && tmp->free_mem >= (size + sizeof(t_block)))
				break ;
			tmp = tmp->next;
		}
		if (tmp)
		{
			block = insert_block_in_page(tmp, size);
		}
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
		if ((size > SMALL_SIZE) || !(block = get_free_block(malloc_type, size)))
		{
			if (!(block = get_new_block(size)))
				return (0);
		}
		return ((void*)(block) + sizeof(t_block));
	}
	return (0);
}
