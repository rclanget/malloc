/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:03:54 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/21 19:23:00 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

#define HEX_STRING "0123456789abcdef"

int		ft_unbrlen(uint64_t nbr, int base)
{
	return ((nbr > 0) ? 1 + ft_unbrlen(nbr / base, base) : 0);
}

void	print_adress(int base, unsigned long i)
{
	if (i < (unsigned long)base)
		write(1, &HEX_STRING[i], 1);
	else
	{
		print_adress(base, i / base);
		write(1, &HEX_STRING[i % base], 1);
	}
}

int		show_all_blocks(t_block *block)
{
	size_t total;

	total = 0;
	while (block)
	{
		if (!block->free)
		{
			print_adress(16, (long long int)((void *)block + sizeof(t_block)));
			ft_print(" - ");
			print_adress(16,
				(long long int)((void *)block + block->size + sizeof(t_block)));
			ft_print(" : %d octets\n", block->size);
			total += block->size;
		}
		block = block->next;
	}
	return (total);
}

int	show_all_pages(t_page *pages)
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

void	show_alloc_mem(void)
{
	size_t total;

	total = show_all_pages(ft_singleton()->tiny);
	total += show_all_pages(ft_singleton()->small);
	total += show_all_pages(ft_singleton()->large);
	ft_print("Total: %d octets\n", total);
}