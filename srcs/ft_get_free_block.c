/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_free_block.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:44:00 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/22 19:50:17 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *ft_get_free_block_in_list(t_type type, size_t size)
{
	t_page *page;
	t_block	*block;

	page = (type == TINY ? ft_singleton()->tiny : ft_singleton()->small);
	block = 0;
	while (page && page->capacity < (size + sizeof(t_block)))
		page = page->next;
	if (page)
	{
		block = page->blocks;
		while (block)
		{
			if (block->free && block->size >= (size + sizeof(t_block)))
			{
				block->free = 0;
				block->parent_page->capacity -= block->size;
				return (block);
			}
			block = block->next;
		}
	}
	return (block);
}

t_block *ft_get_free_block_in_pages(t_type type, size_t size)
{
	t_page *page;
	t_block	*block;

	page = (type == TINY ? ft_singleton()->tiny : ft_singleton()->small);
	block = NULL;
	while (page && page->capacity < size)
		page = page->next;
	if (page)
		block = ft_get_block_in_page(page, size);
	return (block);
}

void *ft_get_free_block(t_type type, size_t size)
{
	t_block *block;

	block = ft_get_free_block_in_list(type, size);
	if (block == NULL)
	{
		block = ft_get_free_block_in_pages(type, size);
	}
	return (block);
}