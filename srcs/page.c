/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 01:44:04 by zipo              #+#    #+#             */
/*   Updated: 2017/01/25 15:31:15 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>

void	add_page(t_page *page)
{
debug("IN\n");
	t_page *head;

	if ((head = g_main_struct.page))
	{
		page->next = head;
		// if (head->prev)
			head->prev = page;
	}
	g_main_struct.page = page;
debug2("OUT\n");
}

size_t	get_page_size(size_t size)
{
debug("IN\n");
	if (size <= TINY_SIZE)
	{
debug2("OUT\n");
		return ((TINY_SIZE + sizeof(t_block)) * 100);
	}
	else if (size > TINY_SIZE && size <= SMALL_SIZE)
	{
debug2("OUT\n");
		return ((SMALL_SIZE + sizeof(t_block)) * 50);
	}
debug2("OUT\n");
	return (size + sizeof(t_block));
}

t_page	*get_new_page(size_t size)
{
debug("IN\n");
	void	*buf;
	t_page	*new_page;
	size_t	page_len;

	page_len = get_page_size(size) + sizeof(t_page);
	page_len = ROUNDUP(page_len);
	if ((buf = mmap(0, page_len, MMAP_FLAG, -1, 0)) != MAP_FAILED)
	{
		new_page = (t_page *)buf;
		ft_bzero(new_page, page_len);
		new_page->type = get_malloc_type(size);
		new_page->free_mem = (page_len - sizeof(t_page));
		new_page->size = (page_len - sizeof(t_page));
		new_page->space = (page_len - sizeof(t_page));
debug2("OUT\n");
		return (new_page);
	}
debug2("OUT\n");
	return (0);
}
