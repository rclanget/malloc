/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:04:52 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/20 16:05:14 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *p, size_t n)
{
	void	*s;

	s = p;
	while (0 != n--)
		*(char *)s++ = 0;
}
