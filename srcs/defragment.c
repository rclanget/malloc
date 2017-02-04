/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 23:04:36 by zipo              #+#    #+#             */
/*   Updated: 2017/01/25 13:29:03 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*buddy_block(t_block *block)
{
	if (((t_block *)((void *)block + sizeof(t_block) + block->size))->is_free)
		return ((t_block *)((void *)block + sizeof(t_block) + block->size));
	return (0);
}

static t_block	*fusion_block(t_block *b1, t_block *b2)
{
	b1->size += (b2->size + sizeof(t_block));
	if ((b1->next = b2->next))
		b1->next->prev = b1;
	if (b2->free_next)
		b2->free_next->free_prev = b2->free_prev;
	if (b2->free_prev)
		b2->free_prev->free_next = b2->free_next;
	else
		g_main_struct.free_block = b2->free_next;
	return (b1);
}

void			defragment(void)
{
	t_block	*free_blocks;
	t_block	*tmp;

	free_blocks = g_main_struct.free_block;
	while (free_blocks)
	{
		if ((tmp = buddy_block(free_blocks)))
		{
			fusion_block(free_blocks, tmp);
			return (defragment());
		}
		free_blocks = free_blocks->free_next;
	}
}
