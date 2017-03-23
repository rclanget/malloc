/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:03:54 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/23 17:13:45 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

#define HEX_STRING "0123456789abcdef"

static void	print_adress(int base, unsigned long i)
{
	if (i < (unsigned long)base)
		write(1, &HEX_STRING[i], 1);
	else
	{
		print_adress(base, i / base);
		write(1, &HEX_STRING[i % base], 1);
	}
}

static int	show_all_blocks(t_block *block)
{
	size_t	total;

	total = 0;
	while (block)
	{
		if (!block->free)
		{
			ft_print("0x");
			print_adress(16, (long long int)((void *)block + sizeof(t_block)));
			ft_print(" - ");
			ft_print("0x");
			print_adress(16,
				(long long int)((void *)block + block->size + sizeof(t_block)));
			ft_print(" : %d octets\n", block->size);
			total += block->size;
		}
		block = block->next;
	}
	return (total);
}

static int	show_all_pages(t_page *pages)
{
	size_t	total;

	total = 0;
	while (pages)
	{
		if (pages->type == TINY)
			ft_print("TINY: 0x");
		if (pages->type == SMALL)
			ft_print("SMALL: 0x");
		if (pages->type == LARGE)
			ft_print("LARGE: 0x");
		print_adress(16, (long long int)pages);
		ft_print("\n");
		total += show_all_blocks(pages->blocks);
		pages = pages->next;
	}
	return (total);
}

void		show_alloc_mem(void)
{
	size_t	total;

	total = show_all_pages(ft_singleton()->tiny);
	total += show_all_pages(ft_singleton()->small);
	total += show_all_pages(ft_singleton()->large);
	ft_print("Total: %d octets\n", total);
}
