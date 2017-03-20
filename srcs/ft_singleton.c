/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_singleton.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:04:25 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/20 16:07:35 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

t_malloc	*ft_singleton(void)
{
	static t_malloc	*ptr = 0;

	if (!ptr)
	{
		ptr = (t_malloc *)mmap(0, sizeof(t_malloc), MMAP_FLAG, -1, 0);
		if (ptr == MAP_FAILED)
			return (0);
		ft_bzero(ptr, sizeof(t_malloc));
	}
	return (ptr);
}
