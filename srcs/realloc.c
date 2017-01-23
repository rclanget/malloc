/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 01:36:41 by zipo              #+#    #+#             */
/*   Updated: 2017/01/23 02:58:57 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*buddy_block(t_block *block)
{
	if (block->prev && block->prev->is_free)
		return (block->prev);
	else if (block->next && block->next->is_free)
		return (block->next);
	return (0);
}

static t_block	*fusion_block(t_block *b1, t_block *b2)
{
	t_block		*ret;
	t_block		*rem;

	ret = (&(*b1) < &(*b2)) ? b1 : b2;
	rem = (&(*b1) < &(*b2)) ? b2 : b1;
	ret->size += (rem->size + sizeof(t_block));
	if ((ret->next = rem->next))
		ret->next->prev = ret;
	if (rem->free_next)
		rem->free_next->free_prev = rem->free_prev;
	if (rem->free_prev)
		rem->free_prev->free_next = rem->free_next;
	else
		g_main_struct->free_block = ret->next;
	return (ret);
}

void			*realloc(void *ptr, size_t size)
{
	t_block		*block;
	t_block		*tmp;

	if (!ptr)
		return (malloc(size));
	if (size)
	{
		block = (t_block *)(ptr - sizeof(t_block));
		while ((block->size <= size) && (tmp = buddy_block(block)))
			block = fusion_block(block, tmp);
		if (block->size <= size && (tmp = malloc(size)))
		{
			ft_memcpy(tmp, block, (block->size + sizeof(t_block)));
			free((void *)block + sizeof(t_block));
			block = tmp;
		}
		return ((void *)block + sizeof(t_block));
	}
	else
		free(ptr);
	return (0);
}
