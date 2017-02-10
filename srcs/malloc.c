/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:38:10 by zipo              #+#    #+#             */
/*   Updated: 2017/01/25 02:25:00 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>

t_main g_main_struct;

void		init_main_struct(void)
{
debug("IN\n");
	if (g_main_struct.init != 1)
	{
		ft_bzero(&g_main_struct, sizeof(t_main));
	}
	g_main_struct.init = 1;
debug2("OUT\n");
}

t_size		get_malloc_type(size_t size)
{
debug("IN\n");
	if (size > 0 && size <= TINY_SIZE)
	{
debug2("OUT\n");
		return (TINY);
	}
	else if (size > TINY_SIZE && size <= SMALL_SIZE)
	{
debug2("OUT\n");
		return (SMALL);
	}
	else if (size > SMALL_SIZE)
	{
debug2("OUT\n");
		return (LARGE);
	}
debug2("OUT\n");
	return (0);
}

t_block		*get_free_block_in_list(size_t size)
{
debug("IN\n");
	t_block	*tmp;

		//write(1, "0", 1);
	tmp = g_main_struct.free_block;
		//write(1, "1", 1);
	while (tmp)
	{
		//write(1, "2", 1);
		if (tmp->size >= size)
		{
		//write(1, "3", 1);
			tmp->parent_page->free_mem -= (tmp->size + sizeof(t_block));
		//write(1, "4", 1);
			if (tmp->free_next)
			{
				//write(1, "a", 1);
				tmp->free_next->free_prev = tmp->free_prev;
			}
		//write(1, "5", 1);
			if (tmp->free_prev)
				tmp->free_prev->free_next = tmp->free_next;
			else
				g_main_struct.free_block = tmp->free_next;
		//write(1, "6", 1);
			tmp->free_next = 0;
			tmp->free_prev = 0;
			tmp->is_free = 0;
		//write(1, "7", 1);
			break ;
		}
		//write(1, "8", 1);
		tmp = tmp->free_next;
	}
		//write(1, "9", 1);
debug2("OUT\n");
	return (tmp);
}

t_block		*get_free_block(t_size type, size_t size)
{
debug("IN\n");
	t_block	*block;
	t_page	*p;

	block = NULL;
	//write(1, "a", 1);
	p = g_main_struct.page;
	//write(1, "b", 1);
	if (!(block = get_free_block_in_list(size)))
	{
		//write(1, "c", 1);
		while (p)
		{
			//write(1, "d", 1);
			if ((p->type == type) && p->space >= (size + sizeof(t_block)))
				break ;
		//write(1, "e", 1);
			p = p->next;
		//write(1, "f", 1);
		}
		//write(1, "g", 1);
		if (p)
		{
			//write(1, "h", 1);
			block = insert_block_in_page(p, size);
		}
		//write(1, "i", 1);
	}
	//write(1, "j", 1);
debug2("OUT\n");
	return (block);
}

void		*malloc(size_t size)
{
debug("IN\n");
	t_block	*block;
	t_size	malloc_type;

	//write(1, "C", 1);
	init_main_struct();
	if ((malloc_type = get_malloc_type(size)))
	{
		//write(1, "1", 1);
		// pthread_mutex_lock(&g_malloc_lock);
		if ((size > SMALL_SIZE) || !(block = get_free_block(malloc_type, size)))
		{
			//write(1, "2", 1);
			if (!(block = get_new_block(size)))
			{
				//write(1, "3", 1);
debug2("OUT\n");
				// pthread_mutex_unlock(&g_malloc_lock);
debug2("OUT\n");// with ptr: %p\n", (void *)0);
				return (0);
			}
			//write(1, "4", 1);
		}
		// pthread_mutex_unlock(&g_malloc_lock);
		//write(1, "5", 1);	
void * ____A = (void *)((char *)block + sizeof(t_block));
debug2("OUT\n");// ptr: %p\n", ____A);
		return (____A);//(void*)((block) + sizeof(t_block)));
	}
debug2("OUT\n");// with ptr: %p\n", (void *)0);
	return (0);
}
