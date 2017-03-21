/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:58:21 by rclanget          #+#    #+#             */
/*   Updated: 2017/03/21 19:44:09 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <unistd.h>

#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

# define MMAP_FLAG		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON
# define PAGESIZE   	(getpagesize())
# define ROUNDUP(x)     ((((x) + PAGESIZE - 1) / PAGESIZE) * PAGESIZE)
# define TINY_SIZE		(PAGESIZE / 16)
# define SMALL_SIZE 	(PAGESIZE / 4)

struct s_page;

typedef enum		e_type
{
	TINY = 1,
	SMALL = 2,
	LARGE = 3
}					t_type;

typedef struct		s_block
{
	int				magic_1; // 0x29a
	size_t			size;
	char			free;
	struct s_page	*parent_page;
	struct s_block	*next;
}					t_block;

typedef struct		s_page
{
	t_type			type;
	size_t			size;
	size_t			capacity;
	size_t			offset;
	t_block			*blocks;
	struct s_page	*next;
}					t_page;

typedef struct		s_malloc
{
	t_page			*large;
	t_page			*small;
	t_page			*tiny;
	t_block			*free_blocks;
}					t_malloc;

/*
*	ft_memcpy.c
*/
void				*ft_memcpy(void *dest, const void *src, size_t n);

/*
*	ft_bzero.c
*/
void				ft_bzero(void *p, size_t n);

/*
*	ft_singleton.c
*/
t_malloc			*ft_singleton(void);

/*
*	ft_print.c
*/
int					ft_print(const char *fmt, ...);

void	ft_putstr_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
int ft_strlen(const char *str);



void *reallocf(void *ptr, size_t size);





/*
* 	ft_get_block_in_page.c
*/
t_block				*ft_get_block_in_page(t_page *page, size_t size);

/*
* 	ft_get_new_block.c
*/
void				*ft_get_new_block(t_type type, size_t size);

/*
* 	ft_get_free_block.c
*/
void				*ft_get_free_block(t_type type, size_t size);

/*
*	show_alloc_mem.c
*/
void				show_alloc_mem(void);

/*
*	realloc.c
*/
void				*calloc(size_t count, size_t size);

/*
*	realloc.c
*/
void				*realloc(void *ptr, size_t size);

/*
*	free.c
*/
void				ft_free(void *ptr);
void				free(void *ptr);

/*
*	malloc.c
*/
void				*ft_malloc(size_t size);
void				*malloc(size_t size);

#endif