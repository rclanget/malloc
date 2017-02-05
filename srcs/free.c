/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 16:56:17 by zipo              #+#    #+#             */
/*   Updated: 2017/01/25 20:11:42 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>
#include <sys/mman.h>

#include <stdio.h>
#define IS_PAGE_EMPTY(x) (x->size == x->free_mem)

void	add_before(t_block *list, t_block *new)
{
	t_block *tmp;

	if ((tmp = list->free_prev))
		tmp->free_next = new;
	list->free_prev = new;
	new->free_next = list;
	new->free_prev = tmp;
	if (!tmp)
		g_main_struct.free_block = new;
}

void	add_after(t_block *list, t_block *new)
{
	if ((new->free_next = list->free_next))
		list->free_next->free_prev = new;
	list->free_next = new;
	new->free_prev = list;
}

void	add_free_block_to_list(t_block *block)
{
	t_block	*free_block_list;

	if ((free_block_list = g_main_struct.free_block))
	{
		while (free_block_list)
		{
			if (free_block_list->size >= block->size)
			{
				add_before(free_block_list, block);
				return ;
			}
			if (!free_block_list->free_next)
				break ;
			free_block_list = free_block_list->free_next;
		}
		add_after(free_block_list, block);
	}
	else
		g_main_struct.free_block = block;
}

void	free_page(t_page *page)
{
	if (page->next)
		page->next->prev = page->prev;
	if (page->prev)
		page->prev->next = page->next;
	else
		g_main_struct.page = page->next;
	if (munmap(page, page->size + sizeof(t_page)) == -1)
		ft_fdprint(2, "Error: munmap\n");
}

void	free(void *ptr)
{
	t_block	*container;

	pthread_mutex_lock(&g_malloc_lock);
	if (ptr && check_adress(ptr))
	{
		container = (t_block *)((void *)ptr - sizeof(t_block));
		container->is_free = 1;
		container->parent_page->free_mem += (container->size + sizeof(t_block));
		if (IS_PAGE_EMPTY(container->parent_page) &&
			(container->parent_page->type == LARGE ||
			(container->parent_page->next || container->parent_page->prev)))
			free_page(container->parent_page);
		else
		{
			add_free_block_to_list(container);
			defragment();
		}
	}
	else
		ft_fdprint(2, "Error: free(): invalid pointer\n");
	pthread_mutex_unlock(&g_malloc_lock);
}
