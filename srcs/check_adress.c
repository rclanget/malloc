/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_adress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:26:21 by zipo              #+#    #+#             */
/*   Updated: 2017/01/23 23:37:52 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	check_adress(void *adress)
{
	t_page	*page;
	t_block *block;

	page = g_main_struct->page;
	while (page)
	{
		block = page->block_list;
		while (block)
		{
			if (!block->is_free && ((void *)block + sizeof(t_block)) == adress)
				return (1);
			block = block->next;
			printf("coucou\n");
		}
		page = page->next;
	}
	return (0);
}
