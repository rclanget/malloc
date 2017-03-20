/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 19:00:08 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/20 19:35:11 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <string.h>

void *realloc(void *ptr, size_t size)
{
	void *new;
	t_block *block;
	size_t ptr_size;

	if (!ptr)
		return (NULL);
	block = (t_block *)(ptr - sizeof(t_block));
	if (block->free)
		return (NULL);
	new = malloc(size);
	ptr_size = block->size;
	memcpy(new, ptr, ptr_size);
	free(ptr);
	return (new);
}