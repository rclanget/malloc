/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:56:40 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/21 18:59:14 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		((char*)dest)[counter] = ((char*)src)[counter];
		counter++;
	}
	return (dest);
}