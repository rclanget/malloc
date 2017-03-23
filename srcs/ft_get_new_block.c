/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_new_block.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:46:32 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/23 15:15:28 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

static t_page	*ft_get_new_large_page(size_t size)
{
	size_t		round_size;
	t_page		*new;

	round_size = ROUNDUP(size + sizeof(t_page) + sizeof(t_block));
	new = (t_page *)mmap(0, round_size, MMAP_FLAG, -1, 0);
	if (new == MAP_FAILED)
		return (NULL);
	ft_bzero(new, round_size);
	new->type = LARGE;
	new->size = round_size - sizeof(t_page);
	new->capacity = round_size - sizeof(t_page);
	new->offset = 0;
	new->next = ft_singleton()->large;
	ft_singleton()->large = new;
	return (new);
}

static t_page	*ft_get_new_page(t_type type)
{
	size_t		size;
	size_t		round_size;
	t_page		*new;

	size = ((type == TINY ? TINY_SIZE : SMALL_SIZE) + sizeof(t_block)) * 100;
	round_size = ROUNDUP(size + sizeof(t_page));
	new = (t_page *)mmap(0, round_size, MMAP_FLAG, -1, 0);
	if (new == MAP_FAILED)
		return (NULL);
	ft_bzero(new, round_size);
	new->type = type;
	new->size = round_size - sizeof(t_page);
	new->capacity = round_size - sizeof(t_page);
	if (type == TINY)
	{
		new->next = ft_singleton()->tiny;
		ft_singleton()->tiny = new;		
	}
	else
	{
		new->next = ft_singleton()->small;
		ft_singleton()->small = new;		
	}
	return (new);
}

void			*ft_get_new_block(t_type type, size_t size)
{
	t_page		*new_page;
	t_block		*new_block;

	new_block = NULL;
	if (type == LARGE)
		new_page = ft_get_new_large_page(size);
	else
		new_page = ft_get_new_page(type);
	if (new_page)
		new_block = ft_get_block_in_page(new_page, size);
	return (new_block);
}