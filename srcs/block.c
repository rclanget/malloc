/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 01:40:54 by zipo              #+#    #+#             */
/*   Updated: 2017/01/23 02:59:54 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*insert_block_in_page(t_page *page, size_t size)
{
	t_block	*block;

	block = (t_block *)((void *)page + (page->size - page->free_mem) + sizeof(t_page));
	ft_bzero(block, sizeof(t_block));
	block->size = size;
	block->parent_page = page;
	block->next = page->block_list;
	if (page->block_list)
		page->block_list->prev = block;
	page->block_list = block;
	page->free_mem -= (size + sizeof(t_block));
	return (block);
}

t_block	*get_new_block(size_t size)
{
	t_page	*new_page;
	t_block	*new_block;

	if ((new_page = get_new_page(size)))
	{
		new_block = insert_block_in_page(new_page, size);
		add_page(new_page);
		return (new_block);
	}
	else
		return (0);
}
