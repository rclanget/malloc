/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_block_in_page.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:23:16 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/22 20:32:00 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *ft_get_block_in_page(t_page *page, size_t size)
{
	t_block		*block;

	if (page->size < (page->offset + size + sizeof(t_block)))
		return (NULL);
	block = (t_block *)((void *)(char *)page + (page->offset + sizeof(t_page)));
	block->magic_1 = 0x29a;
	block->size = size;
	block->parent_page = page;
	block->next = page->blocks;
	page->blocks = block;
	page->capacity -= (size + sizeof(t_block));
	page->offset += (size + sizeof(t_block));
	return (block);
}