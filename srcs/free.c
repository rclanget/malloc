/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:42:13 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/23 16:53:22 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

static void	ft_remove_page(t_page *page)
{
	t_page *list;

	if (page->type == LARGE)
		list = ft_singleton()->large;
	else if (page->type == SMALL)
		list = ft_singleton()->small;
	else
		list = ft_singleton()->tiny;
	while (list)
	{
		if (list->next && list->next == page)
		{
			list->next = list->next->next;
			munmap(page, page->size + sizeof(t_page));
			return ;
		}
		list = list->next;
	}
}

static void	ft_page_update(t_page *page, size_t block_size)
{
	if (page)
	{
		page->capacity += block_size;
		if ((page->capacity + sizeof(t_block)) == page->size)
		{
			ft_remove_page(page);
		}
	}
}

void		ft_free(void *ptr)
{
	t_block *block;

	if (ptr && *((char *)ptr))
	{
		block = (t_block *)((void *)(char *)ptr - sizeof(t_block));
		if (block && block->magic_1 == 0x29a)
		{
			block->free = 1;
			ft_page_update(block->parent_page, block->size);
		}
	}
}

void		free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}
