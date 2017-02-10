/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 01:59:12 by zipo              #+#    #+#             */
/*   Updated: 2017/01/24 02:39:52 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
debug("IN\n");
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
debug("IN\n");
	int	i;

	i = 0;
	while (str[i])
		ft_putchar_fd(str[i++], fd);
debug2("OUT\n");
}

void	ft_putnbr_fd(int n, int fd)
{
debug("IN\n");
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			n = n * -1;
			ft_putchar_fd('-', fd);
		}
		if (n >= 0 && n < 10)
			ft_putchar_fd((n + 48), fd);
		else
		{
			ft_putnbr_fd((n / 10), fd);
			ft_putnbr_fd((n % 10), fd);
		}
	}
debug2("OUT\n");
}
