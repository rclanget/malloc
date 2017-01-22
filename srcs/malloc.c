/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:38:10 by zipo              #+#    #+#             */
/*   Updated: 2017/01/23 00:43:18 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>

void init_main_struct(void)
{
	void *buf;

	if (g_main_struct)
		return ;
	if ((buf = mmap(NULL, sizeof(g_main_struct), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) != (void *)-1)
	{
		g_main_struct = (t_main *)buf;
		ft_bzero(g_main_struct, sizeof(t_main));
		g_main_struct->init = 1;
	}
}

/*
*		Insert un block dans une page
*/
t_block	*insert_block_in_page(t_page *page, size_t size)
{
	t_block	*block;

	block = (t_block *)((void *)page + (page->size - page->free_mem) + sizeof(t_page));
	ft_bzero(block, sizeof(t_block));
	block->size = size;
	block->parent_page = page;
	block->next = page->block_list;
	if (page->block_list)
		page->block_list->prev = block;
	page->block_list = block;
	page->free_mem -= (size + sizeof(t_block));
	return (block);
}

/*
*		Ajoute une page à la liste globale
*/
void	add_page(t_page *page)
{
	t_page *head;

	head = g_main_struct->page;
	if (head)
	{
		page->next = head;
		if (head->prev)
			head->prev = page;
	}
	g_main_struct->page = page;
}

/*
*		Retourne le type de malloc, TINY, SMALL ou LARGE
*/
t_size	get_malloc_type(size_t size)
{
	if (size > 0 && size <= 128)
		return (TINY);
	else if (size > 128 && size <= 1024)
		return (SMALL);
	else if (size > 1024)
		return (LARGE);
	else
		return (0);
}

/*
*		Calcul la taile de la page !!!!!!!!!!!!!!!! à modifier (prendre en compte getpagesize)
*/
size_t	get_page_size(size_t size)
{
	if (size <= 128)
		return (128 * 100);
	else if (size > 128 && size <= 1024)
		return (1024 * 50);
	else
		return (size);
}

/*
*		Alloue une nouvelle page
*/
t_page	*get_new_page(size_t size)
{
	void	*buf;
	t_page	*new_page;
	size_t	page_len;

	page_len = get_page_size(size) + sizeof(t_page);
	page_len = ROUNDUP(page_len);
	if ((buf = mmap(NULL, page_len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) != (void *)-1)
	{
		new_page = (t_page *)buf;
		ft_bzero(new_page, page_len);
		new_page->type = get_malloc_type(size);
		new_page->free_mem = (page_len - sizeof(t_page));
		new_page->size = (page_len - sizeof(t_page));
		return (new_page);
	}
	return (0);
}

/*
*		Alloue un nouveau block, et donc une nouvelle page aussi
*/
t_block	*get_new_block(size_t size)
{
	t_page	*new_page;
	t_block	*new_block;

	if ((new_page = get_new_page(size)))
	{
		new_block = insert_block_in_page(new_page, size);
		add_page(new_page);
		return (new_block);
	}
	else
		return (0);
}

/*
*		Recherche un block libre dans la liste
*/
t_block	*get_free_block_in_list(size_t size)
{
	t_block	*tmp;

	tmp = g_main_struct->free_block;
	int i = 0;
	while (tmp)
	{
		if (tmp->size >= size)
			break ;
		tmp = tmp->free_next;
		if (i++ > 3)
			break ;
	}
	if (tmp)
	{
		tmp->parent_page->free_mem -= (tmp->size + sizeof(t_block));
		if (tmp->free_next)
			tmp->free_next->free_prev = tmp->free_prev;
		if (tmp->free_prev)
			tmp->free_prev->free_next = tmp->free_next;
		else
			g_main_struct->free_block = tmp->free_next;
		tmp->free_next = 0;
		tmp->free_prev = 0;
		tmp->is_free = 0;
	}
	return (tmp);
}

/*
*		Vérifie s'il y a de la place dans la liste de block free OU à défault
*		dans les pages TINY ET SMALL si concerné
*/
t_block	*get_free_block(t_size type, size_t size)
{
	t_block	*block;
	t_page	*tmp;

	block = NULL;
	tmp = g_main_struct->page;
	if (!(block = get_free_block_in_list(size)))
	{
		while (tmp)
		{
			if ((tmp->type == type) && tmp->free_mem >= (size + sizeof(t_block)))
				break ;
			tmp = tmp->next;
		}
		if (tmp)
		{
			block = insert_block_in_page(tmp, size);
		}
	}
	return (block);
}

t_block	*buddy_block(t_block *block)
{
	if (block->prev && block->prev->is_free)
		return (block->prev);
	else if (block->next && block->next->is_free)
		return (block->next);
	return (0);
}

t_block	*fusion_block(t_block *b1, t_block *b2)
{
	t_block *ret;
	t_block	*rem;

	ret = (&(*b1) < &(*b2)) ? b1 : b2;
	rem = (&(*b1) < &(*b2)) ? b2 : b1;
	ret->size += (rem->size + sizeof(t_block));
	if ((ret->next = rem->next))
		ret->next->prev = ret;
	if (rem->free_next)
		rem->free_next->free_prev = rem->free_prev;
	if (rem->free_prev)
		rem->free_prev->free_next = rem->free_next;
	else
		g_main_struct->free_block = rem->next;
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_block *tmp;
	t_page	*page;

	// On recupere la structure du block
	block = (t_block *)(ptr - sizeof(t_block));
	// tant que le block avant ou apres est free, et que le block actuel ne dispose
	// pas d'assez de place, on fusionne
	while ((block->size <= size) && (tmp = buddy_block(block)))
		block = fusion_block(block, tmp);
	// Si les deux conditions ne sont plus remplis et que le block est toujours trop petit
	// Alors on alloue un nouvel emplacement et on free l'existant;
	if (block->size <= size)
	{
		tmp = malloc(size);
		ft_memcpy(tmp, block, (block->size + sizeof(t_block)));
		free((void *)block + sizeof(t_block));
		block = tmp;
	}
	return ((void *)block + sizeof(t_block));
}

void	*malloc(size_t size)
{
	t_block	*block;
	t_size	malloc_type;

	init_main_struct();
	// On récupère la taille du malloc (TINY, SMALL ou LARGE)
	if ((malloc_type = get_malloc_type(size)))
	{
		// On regarde si on dispose de l'espace suffisant pour contenir le malloc
		if ((size > 1024) || !(block = get_free_block(malloc_type, size)))
		{
			// Sinon on alloue un nouveau block
			if (!(block = get_new_block(size)))
				return (0);
		}
		return ((void*)(block) + sizeof(t_block));
	}
	return (0);
}
