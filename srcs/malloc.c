/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:38:10 by zipo              #+#    #+#             */
/*   Updated: 2017/01/21 03:06:03 by zipo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>

size_t	get_page_size(size_t size);

t_main	*g_main_struct = NULL;

#define GETPAGESIZE		(getpagesize())
#define ROUNDUP(x)		(((x + GETPAGESIZE - 1) / GETPAGESIZE) * GETPAGESIZE)

void	ft_bzero(void *s, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		*((char*)s + counter) = '\0';
		counter++;
	}
}

void init_main_struct(void)
{
	t_main	*buf;

	if (g_main_struct)
		return ;
	if ((buf = mmap(NULL, sizeof(g_main_struct), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) != (void *)-1)
	{
		g_main_struct = buf;
		ft_bzero(g_main_struct, sizeof(g_main_struct));
	}
}

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

/*
*		Insert un block dans une page
*/
t_block	*insert_block_in_page(t_page *page, size_t size)
{
	t_block	*block;
	size_t	page_len;

	page_len = get_page_size(size) + sizeof(t_page);
	page_len = ROUNDUP(page_len);
	block = (t_block *)((void *)page + (page_len - page->free_mem));
	block->size = size;
	block->is_free = 0;
	block->parent_page = page;
	block->next = page->block_list;
	block->prev = 0;
	block->free_next = 0;
	block->free_prev = 0;
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
	if (page->size == TINY)
	{
		page->next = g_main_struct->tiny_page;
		if (g_main_struct->tiny_page)
			g_main_struct->tiny_page->prev = page;
		g_main_struct->tiny_page = page;
	}
	else if (page->size == SMALL)
	{
		page->next = g_main_struct->small_page;
		if (g_main_struct->small_page)
			g_main_struct->small_page->prev = page;
		g_main_struct->small_page = page;
	}
	else if (page->size == LARGE)
	{
		page->next = g_main_struct->large_page;
		if (g_main_struct->large_page)
			g_main_struct->large_page->prev = page;
		g_main_struct->large_page = page;
	}
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
		new_page->size = get_malloc_type(size);
		new_page->block_list = 0;
		new_page->next = 0;
		new_page->prev = 0;
		new_page->free_mem = (page_len - sizeof(t_page));
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
	while (tmp)
	{
		if (tmp->size >= size)
			break ;
		tmp = tmp->free_next;
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
	t_page	*tmp;
	t_block	*block;

	if (type == TINY)
		tmp = g_main_struct->tiny_page;
	if (type == SMALL)
		tmp = g_main_struct->small_page;
	if (type == LARGE)
		tmp = g_main_struct->large_page;
	block = NULL;
	if (!(block = get_free_block_in_list(size)))
	{
		while (tmp)
		{
			if (tmp->free_mem >= (size + sizeof(t_block)))
				break ;
			tmp = tmp->next;
		}
		if (tmp)
			block = insert_block_in_page(tmp, size);
	}
	return (block);
}

void	add_free_block_to_list(t_block *block)
{
	t_block	*free_block_list;

	if ((free_block_list = g_main_struct->free_block))
	{
		if (!free_block_list->free_next && free_block_list->size > block->size)
		{
			block->free_next = free_block_list;
			free_block_list->free_prev = block;
			g_main_struct->free_block = block;
		}
		else
		{
			while (free_block_list->free_next)
			{
				if (free_block_list->free_next->size >= block->size)
					break;
				free_block_list = free_block_list->free_next;
			}
			block->free_next = free_block_list->free_next;
			block->free_prev = block;
			free_block_list->free_next = block;
			block->free_prev = free_block_list;
		}
	}
	else
		g_main_struct->free_block = block;
}

// void	*realloc(void *ptr, size_t size)
// {
//
// }

#include <errno.h>
#include <string.h>
void	free(void *ptr)
{
	t_block	*block_container;
	t_page	*page_container;
	size_t	page_len;

	if (ptr)
	{
		block_container = (t_block *)(ptr - sizeof(t_block));
		page_container = block_container->parent_page;
		block_container->is_free = 1;
		page_container->free_mem += (block_container->size + sizeof(t_block));
		page_len = get_page_size(block_container->size) + sizeof(t_page);
		page_len = ROUNDUP(page_len);
		if (page_container->free_mem == (page_len - sizeof(t_page)) && (page_container->next || page_container->prev))
		{
			// Si c'est la première page, on fait pointer g_main_struct->TYPE_PAGE sur la page suivante
			if (!page_container->prev)
			{
				if (page_container->size == TINY)
					g_main_struct->tiny_page = page_container->next;
				else if (page_container->size == SMALL)
					g_main_struct->small_page = page_container->next;
				else if (page_container->size == LARGE)
					g_main_struct->large_page = page_container->next;
			}
			else
			{
				if (page_container->prev)
					page_container->prev->next = page_container->next;
				if (page_container->next)
					page_container->next->prev = page_container->prev;
			}
			if (munmap(page_container, page_len) == -1)
				printf("ERROR MUNMAP: %s\ngetpagesize: %d\n", strerror(errno), getpagesize());
		}
		else
			add_free_block_to_list(block_container);
	}
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
		if (!(block = get_free_block(malloc_type, size)))
		{
			// Sinon on alloue un nouveau block
			if (!(block = get_new_block(size)))
				return (0);
		}
		return ((void*)(block) + sizeof(t_block));
	}
	return (0);
}

// ****************************** TEST MAIN ********************************* //
void print_page(void)
{
	int j = 0;
	t_page *tmp = g_main_struct->tiny_page;

	printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	while (tmp)
	{
		j++;
		printf("Page: %d, size: %d, free mem: %ld\n-----------------------\n", j, tmp->size, tmp->free_mem);
		tmp = tmp->next;
	}
	tmp = g_main_struct->small_page;
	while (tmp)
	{
		j++;
		printf("Page: %d, size: %d, free mem: %ld\n-----------------------\n", j, tmp->size, tmp->free_mem);
		tmp = tmp->next;
	}
	tmp = g_main_struct->large_page;
	while (tmp)
	{
		j++;
		printf("Page: %d, size: %d, free mem: %ld\n-----------------------\n", j, tmp->size, tmp->free_mem);
		tmp = tmp->next;
	}
	printf("Nombre de page: %d\n", j);

}

int main(void)
{

	// printf("%d\n", roundUp((8192 + sizeof(t_page)), 4096));
	// str = (char **)malloc(sizeof(char *) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *str = (char *)malloc(sizeof(char) * 1024);
	// print_page();

	// ------- Test 1 -----------
	char *str;
	int i = 0;
	while (i < 1024)
	{
		str = malloc(1024);
		if (i % 2)
			free(str);
		i++;
	}
	print_page();

	// ------- Test free -----------
	// char *str;

	printf("--- START ---\n");
	str = (char *)malloc(8);
	free(str);
	printf("1\n");
	str = (char *)malloc(16);
	free(str);
	printf("2\n");
	str = (char *)malloc(32);
	free(str);
	printf("3\n");
	str = (char *)malloc(16);
	free(str);
	str[0] = 'a';
	printf("%s\n", str);
	return (0);
}
