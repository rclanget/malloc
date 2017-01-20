/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:38:10 by zipo              #+#    #+#             */
/*   Updated: 2017/01/20 13:31:31 by zipo             ###   ########.fr       */
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
	block->next = page->block_list;
	block->prev = 0;
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
		g_main_struct->tiny_page = page;
	}
	else if (page->size == SMALL)
	{
		page->next = g_main_struct->small_page;
		g_main_struct->small_page = page;
	}
	else if (page->size == LARGE)
	{
		page->next = g_main_struct->large_page;
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
		tmp = tmp->next;
	}
	return (tmp);
}

/*
*		Alloue un nouveau block, et donc une nouvelle page aussi
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
			if (tmp->size == type && tmp->free_mem >= (size + sizeof(t_block)))
				break ;
			tmp = tmp->next;
		}
		if (tmp)
			block = insert_block_in_page(tmp, size);
	}
	return (block);
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
		return ((void*)(block));
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
	int i = 0;
	while (i < 1024)
	{
		malloc(1024);
		i++;
	}
	print_page();
	return (0);
}
