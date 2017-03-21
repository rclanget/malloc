/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:29:59 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/21 19:44:49 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void *ptr;

	ft_print("calloc_in\n");
	pthread_mutex_lock(&mutex);
	ptr = ft_malloc(count * size);
	if (ptr)
	{
		ft_bzero(ptr, count * size);
	}
	pthread_mutex_unlock(&mutex);
	ft_print("calloc_end\n");
	return (ptr);
}