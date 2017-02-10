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

#include <unistd.h>

void	add_free_block_to_list(t_block *block)
{
	// t_block	*fbl;

	// if ((free_block_list = g_main_struct.free_block))
	// {
	// 	while (free_block_list)
	// 	{
	// 		if (free_block_list->size >= block->size)
	// 		{
	// 			add_before(free_block_list, block);
	// 			return ;
	// 		}
	// 		if (!free_block_list->free_next)
	// 			break ;
	// 		free_block_list = free_block_list->free_next;
	// 	}
	// 	add_after(free_block_list, block);
	// }
	// else
	// 	g_main_struct.free_block = block;

	block->free_prev = 0;
	if ((block->free_next = g_main_struct.free_block))
	{
		write(1, "a", 1);
		// g_main_struct.free_block->free_prev = block;
		write(1, "b", 1);
	}
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
	write(1, "X", 1);
	if (munmap((void *)page, page->size + sizeof(t_page)) == -1)
		ft_fdprint(2, "Error: munmap\n");
}

int coconut_page(t_size type)
{
	int i = 0;
	t_page *page = g_main_struct.page;

	if (type == LARGE)
		return (10);
	while (page)
	{
		if (page->type == type)
			++i;
		page = page->next;
	}
	return (i);
}

void	free(void *ptr)
{
	t_block	*container;

	// pthread_mutex_lock(&g_malloc_lock);
		write(1, "0", 1);
	if (ptr && check_adress(ptr))
	{
		write(1, "1", 1);
		container = (t_block *)((void *)ptr - sizeof(t_block));
		container->is_free = 1;
		container->parent_page->free_mem += (container->size + sizeof(t_block));
		write(1, "2", 1);
		if (IS_PAGE_EMPTY(container->parent_page) &&
		coconut_page(container->parent_page->type) > 1)
			{
				write(1, "c", 1);
			free_page(container->parent_page);
				write(1, "d", 1);
			}
		else
		{
		write(1, "3", 1);
			add_free_block_to_list(container);
		write(1, "4", 1);
			// defragment();
		}
	}
	else
		ft_fdprint(2, "Error: free(): invalid pointer\n");
	write(1, "5", 1);
	// pthread_mutex_unlock(&g_malloc_lock);
}
