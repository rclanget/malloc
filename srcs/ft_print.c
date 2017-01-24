/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 01:56:30 by zipo              #+#    #+#             */
/*   Updated: 2017/01/24 02:40:25 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdarg.h>

void	print_arg(va_list ap, const char *fmt, int fd)
{
	if (*fmt == 's')
		ft_putstr_fd(va_arg(ap, char *), fd);
	else if (*fmt == 'c')
		ft_putchar_fd(va_arg(ap, int), fd);
	else if (*fmt == 'd')
		ft_putnbr_fd(va_arg(ap, int), fd);
}

void	ft_fdprint(int fd, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	while (fmt && *fmt)
	{
		if (*fmt == '%')
			print_arg(ap, ++fmt, fd);
		else
			write(fd, fmt, 1);
		fmt++;
	}
	va_end(ap);
}

void	ft_print(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	while (fmt && *fmt)
	{
		if (*fmt == '%')
			print_arg(ap, ++fmt, 1);
		else
			write(1, fmt, 1);
		fmt++;
	}
	va_end(ap);
}
