/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 16:50:27 by zipo              #+#    #+#             */
/*   Updated: 2017/01/21 16:54:56 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
debug("IN\n");
	size_t counter;

	counter = 0;
	while (counter < n)
	{
		*((char *)s + counter) = '\0';
		counter++;
	}
debug2("OUT\n");
}
