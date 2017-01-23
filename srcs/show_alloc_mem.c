/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:53:15 by zipo              #+#    #+#             */
/*   Updated: 2017/01/23 23:17:30 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>
#include <time.h>

void 	ft_putchar(char str)
{
	write(1, &str, 1);
}

void 	ft_putstr(char *str)
{
	while (str && *str)
		write(1, str++, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			n = n * -1;
			ft_putchar('-');
		}
		if (n >= 0 && n < 10)
			ft_putchar((n) + 48);
		else
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
	}
}

int ft_unbrlen(uint64_t nbr, int base)
{
	return ((nbr > 0) ? 1 + ft_unbrlen(nbr / base, base) : 0);
}

int convert(int base, unsigned long long int i, int capitals, int sign)
{
	char *str;

	str = "0123456789abcdef0123456789ABCDEF";
	if (sign == -1)
		write(1, "-", 1);
	if (i < (unsigned long long int)base)
		write(1, &str[i + capitals], 1);
	else
	{
		convert(base, i / base, capitals, 1);
		write(1, &str[(i % base) + capitals], 1);
	}
	return ((sign == -1) ? ft_unbrlen(i, base) + 1 : ft_unbrlen(i, base));
}

void    show_all_blocks(t_block *block)
{
	while (block)
	{
		if (!block->is_free)
		{
			convert(16, (long long int)((void *)block + sizeof(t_block)), 0, 0);
			ft_putstr(" - ");
			convert(16, (long long int)((void *)block + block->size + sizeof(t_block)), 0, 0);
			ft_putstr(" : ");
			ft_putnbr(block->size);
			ft_putstr(" octets\n");
			// ft_putstr("%p - %p : %ld octets\n", &(*block),	((void*)block->size + sizeof(t_block)), block->size);
		}
		block = block->next;
	}
}

void    show_all_pages(t_page *pages)
{
	size_t	total;

	total = 0;
	while (pages)
	{
		if (pages->type == TINY)
			ft_putstr("TINY: 0x");
		if (pages->type == SMALL)
			ft_putstr("SMALL: 0x");
		if (pages->type == LARGE)
			ft_putstr("LARGE: 0x");
		convert(16, (long long int)pages, 0, 0);
		ft_putstr("\n");
		show_all_blocks(pages->block_list);
		total += (pages->size - pages->free_mem);
		pages = pages->next;
	}
	ft_putstr("Total: ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}

void    show_alloc_mem(void)
{
	show_all_pages(g_main_struct->page);
}
