/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:42:13 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/20 18:47:14 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void free(void *ptr)
{
	t_block *block;

	block = (t_block *)((char *)ptr - sizeof(t_block));
	if (block && block->magic_1 == 0x29a)
	{
		block->free = 1;
		block->free_next = ft_singleton()->free_blocks;
		ft_singleton()->free_blocks = block;
	}
}