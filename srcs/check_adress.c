/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_adress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:26:21 by zipo              #+#    #+#             */
/*   Updated: 2017/01/25 12:03:49 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

int	check_adress(void *adress)
{
debug("IN\n");
	t_page	*page;
	t_block *block;

	page = g_main_struct.page;
	while (adress && page)
	{
		block = page->block_list;
		while (block)
		{
			if (!block->is_free && ((void *)block + sizeof(t_block)) == adress)
			{
debug2("OUT\n");
				return (1);
			}
			block = block->next;
		}
		page = page->next;
	}
debug2("OUT\n");
	return (0);
}
