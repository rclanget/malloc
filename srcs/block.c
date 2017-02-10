/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 01:40:54 by zipo              #+#    #+#             */
/*   Updated: 2017/01/24 02:18:04 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*insert_block_in_page(t_page *p, size_t size)
{
	t_block	*block;

	block = (t_block *)((void *)p + (p->size - p->space) + sizeof(t_page));
	ft_bzero(block, sizeof(t_block) + size);
	block->size = size;
	block->parent_page = p;
	block->magic_1 = 0x29a;
	block->magic_2 = 0x29a;
	if ((block->next = p->block_list))
		p->block_list->prev = block;
	p->block_list = block;
	p->free_mem -= (size + sizeof(t_block));
	p->space -= (size + sizeof(t_block));
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
