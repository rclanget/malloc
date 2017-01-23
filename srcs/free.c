/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 16:56:17 by zipo              #+#    #+#             */
/*   Updated: 2017/01/23 03:00:03 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>
#include <sys/mman.h>

#include <errno.h>

static void	add_free_block_to_list(t_block *block)
{
	t_block	*free_block_list;

	if ((free_block_list = g_main_struct->free_block))
	{
		if (free_block_list->size > block->size)
		{
			block->free_next = free_block_list;
			free_block_list->free_prev = block;
			g_main_struct->free_block = block;
		}
		else
		{
			while (free_block_list->free_next)
			{
				if (free_block_list->free_next->size >= block->size)
					break;
				free_block_list = free_block_list->free_next;
			}
			block->free_next = free_block_list->free_next;
			block->free_prev = block;
			free_block_list->free_next = block;
			block->free_prev = free_block_list;
		}
	}
	else
	{
		g_main_struct->free_block = block;
		block->free_prev = 0;
		block->free_next = 0;
	}
}

static void	free_page(t_page *page)
{
	if (page->next)
		page->next->prev = page->prev;
	if (page->prev)
		page->prev->next = page->next;
	else
		g_main_struct->page = page->next;
	if (munmap(page, page->size + sizeof(t_page)) == -1)
		printf("ERROR MUNMAP: %s\ngetpagesize: %d\n", strerror(errno), getpagesize());
}

int		is_page_empty(t_page *page)
{
	return (page->size == page->free_mem);
}

void	free(void *ptr)
{
	t_block	*block_container;

	if (ptr)
	{
		block_container = (t_block *)(ptr - sizeof(t_block));
		block_container->is_free = 1;
		block_container->parent_page->free_mem += (block_container->size + sizeof(t_block));
		if (is_page_empty(block_container->parent_page) &&
			(block_container->parent_page->type == LARGE || (block_container->parent_page->next || block_container->parent_page->prev)))
			free_page(block_container->parent_page);
		else
			add_free_block_to_list(block_container);
	}
}
