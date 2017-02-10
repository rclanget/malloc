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
debug("IN\n");
	t_block *tmp;

	if ((tmp = list->free_prev))
		tmp->free_next = new;
	list->free_prev = new;
	new->free_next = list;
	new->free_prev = tmp;
	if (!tmp)
		g_main_struct.free_block = new;
debug2("OUT\n");
}

void	add_after(t_block *list, t_block *new)
{
debug("IN\n");
	if ((new->free_next = list->free_next))
		list->free_next->free_prev = new;
	list->free_next = new;
	new->free_prev = list;
debug2("OUT\n");
}

#include <unistd.h>

void	add_free_block_to_list(t_block *block)
{
debug("IN\n");
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
		//write(1, "a", 1);
		// g_main_struct.free_block->free_prev = block;
		//write(1, "b", 1);
	}
	g_main_struct.free_block = block;
debug2("OUT\n");
}

void	free_page(t_page *page)
{
debug("IN\n");
	if (page->next)
		page->next->prev = page->prev;
	if (page->prev)
		page->prev->next = page->next;
	else
		g_main_struct.page = page->next;
	//write(1, "X", 1);
	if (munmap((void *)page, page->size + sizeof(t_page)) == -1)
		ft_fdprint(2, "Error: munmap\n");
debug2("OUT\n");
}

int coconut_page(t_size type)
{
debug("IN\n");
	int i = 0;
	t_page *page = g_main_struct.page;

	if (type == LARGE)
	{
debug2("OUT\n");
		return (10);
	}
	while (page)
	{
		if (page->type == type)
			++i;
		page = page->next;
	}
debug2("OUT\n");
	return (i);
}

void	free(void *ptr)
{
debug("IN\n");
	t_block	*container;

	// pthread_mutex_lock(&g_malloc_lock);
		//write(1, "0", 1);
	if (ptr && check_adress(ptr))
	{
		//write(1, "1", 1);
		container = (t_block *)((void *)ptr - sizeof(t_block));
		container->is_free = 1;
		container->parent_page->free_mem += (container->size + sizeof(t_block));
		//write(1, "2", 1);
		if (IS_PAGE_EMPTY(container->parent_page) &&
		coconut_page(container->parent_page->type) > 1)
			{
				//write(1, "c", 1);
			free_page(container->parent_page);
				//write(1, "d", 1);
			}
		else
		{
		//write(1, "3", 1);
			add_free_block_to_list(container);
		//write(1, "4", 1);
			// defragment();
		}
	}
	else
		ft_fdprint(2, "Error: free(): invalid pointer\n");
	//write(1, "5", 1);
debug2("OUT\n");
	// pthread_mutex_unlock(&g_malloc_lock);
}
