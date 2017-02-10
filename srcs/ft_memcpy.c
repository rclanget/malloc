/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 16:51:06 by zipo              #+#    #+#             */
/*   Updated: 2017/01/21 16:54:51 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
debug("IN\n");
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		((char*)dest)[counter] = ((char*)src)[counter];
		counter++;
	}
debug2("OUT\n");
	return (dest);
}
