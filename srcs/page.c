/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 01:44:04 by zipo              #+#    #+#             */
/*   Updated: 2017/01/23 02:59:38 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <sys/resource.h>
#include <sys/mman.h>

void	add_page(t_page *page)
{
	t_page *head;

	head = g_main_struct->page;
	if (head)
	{
		page->next = head;
		if (head->prev)
			head->prev = page;
	}
	g_main_struct->page = page;
}

size_t	get_page_size(size_t size)
{
	if (size <= 128)
		return (128 * 100);
	else if (size > 128 && size <= 1024)
		return (1024 * 50);
	else
		return (size);
}

t_page	*get_new_page(size_t size)
{
	void	*buf;
	t_page	*new_page;
	size_t	page_len;

	page_len = get_page_size(size) + sizeof(t_page);
	page_len = ROUNDUP(page_len);
	if ((buf = mmap(NULL, page_len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) != (void *)-1)
	{
		new_page = (t_page *)buf;
		ft_bzero(new_page, page_len);
		new_page->type = get_malloc_type(size);
		new_page->free_mem = (page_len - sizeof(t_page));
		new_page->size = (page_len - sizeof(t_page));
		return (new_page);
	}
	return (0);
}
