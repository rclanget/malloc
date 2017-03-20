/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_block_in_page.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:23:16 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/20 18:44:37 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *ft_get_block_in_page(t_page *page, size_t size)
{
	t_block		*block;
	size_t		offset;	

	offset = sizeof(t_page) + (page->size - page->capacity);
	block = (t_block *)((char *)page + offset);
	block->magic_1 = 0x29a;
	block->size = size;
	block->parent_page = page;
	block->next = page->blocks;
	page->blocks = block;
	page->capacity -= size + sizeof(t_block);
	return (block);
}