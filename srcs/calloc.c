/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:26:33 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/22 19:15:53 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>

// void	*ft_calloc(size_t count, size_t size)
// {
// 	size_t	total;
// 	void	*ptr;

// 	total = (count + 1) * size;
// 	ptr = ft_malloc(total);
// 	if (ptr)
// 	{
// 		ft_bzero(ptr, total);
// 	}
// 	return (ptr);
// }

// void	*calloc(size_t count, size_t size)
// {
// 	void *ptr;

// 	pthread_mutex_lock(&mutex);
// 	ptr = ft_calloc(count, size);
// 	pthread_mutex_unlock(&mutex);
// 	return (ptr);
// }