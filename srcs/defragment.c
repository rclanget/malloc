/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 23:04:36 by zipo              #+#    #+#             */
/*   Updated: 2017/01/25 01:49:15 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*buddy_block(t_block *block)
{
	if (((void *)block + sizeof(t_block) + block->size) == block->free_next)
		return (block->free_next);
	return (0);
}

static t_block	*fusion_block(t_block *b1, t_block *b2)
{
	t_block		*ret;
	t_block		*rem;

	ret = (&(*b1) > &(*b2)) ? b1 : b2;
	rem = (&(*b1) > &(*b2)) ? b2 : b1;
	ret->size += (rem->size + sizeof(t_block));
	if ((ret->next = rem->next))
		ret->next->prev = ret;
	if (rem->free_next)
		rem->free_next->free_prev = rem->free_prev;
	if (rem->free_prev)
		rem->free_prev->free_next = rem->free_next;
	else
		g_main_struct->free_block = rem->free_next;
	return (ret);
}

void			defragment(void)
{
	t_block	*free_blocks;
	t_block	*tmp;

	free_blocks = g_main_struct->free_block;
	while (free_blocks)
	{
		if ((tmp = buddy_block(free_blocks)))
			fusion_block(free_blocks, tmp);
		free_blocks = free_blocks->free_next;
	}
}
