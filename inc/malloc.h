/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 17:02:07 by rclanget          #+#    #+#             */
/*   Updated: 2017/02/05 17:02:08 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <pthread.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
int __ident;
#define debug(...) \
		static int called_number = 0; \
		({	\
			char __s[250]; \
			memset(__s, 0, 250); \
			int __a = 0; while (__a < __ident) { sprintf(&__s[strlen(__s)], "  "); ++__a; } \
			sprintf(&__s[strlen(__s)], "\033[32;1m%s(%d)(%d): \033[0m", __FUNCTION__, __LINE__, ++called_number); \
			sprintf(&__s[strlen(__s)], __VA_ARGS__); \
			write(2, __s, 250); \
			++__ident; \
		})
#define debug2(...) \
		({	\
			--__ident; \
			char __s[250]; \
			memset(__s, 0, 250); \
			int __a = 0; while (__a < __ident) { sprintf(&__s[strlen(__s)], "  "); ++__a; } \
			sprintf(&__s[strlen(__s)], "\033[31;1m%s(%d)(%d): \033[0m", __FUNCTION__, __LINE__, called_number); \
			sprintf(&__s[strlen(__s)], __VA_ARGS__); \
			write(2, __s, 250); \
		})



# define PAGESIZE				(getpagesize())
# define ROUNDUP(x)				(((x + PAGESIZE - 1) / PAGESIZE) * PAGESIZE)
# define MMAP_FLAG				PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON
# define OFFSETOF(type, member)	((size_t) &((type *)0)->member)
# define CONTAINEROF(ptr, t, m)	((t *)((char *)(ptr) - OFFSETOF(t, m)))

# define TINY_SIZE				128
# define SMALL_SIZE				1024

struct s_page;

typedef struct					s_block
{
	int							magic_1;
	size_t						size;
	int							is_free;
	struct s_page				*parent_page;
	struct s_block				*next;
	struct s_block				*prev;
	struct s_block				*free_next;
	struct s_block				*free_prev;
	int							magic_2;
}								t_block;

typedef enum					e_size
{
	TINY = 1,
	SMALL = 2,
	LARGE = 3
}								t_size;

typedef struct					s_page
{
	t_size						type;
	size_t						size;
	size_t						free_mem;
	size_t						space;
	t_block						*block_list;
	struct s_page				*next;
	struct s_page				*prev;
}								t_page;

typedef struct					s_main
{
	int							init;
	t_page						*page;
	t_block						*free_block;
}								t_main;

extern t_main					g_main_struct;
pthread_mutex_t					g_malloc_lock;

void							*malloc(size_t size);
void							*realloc(void *ptr, size_t size);
void							free(void *ptr);
void							show_alloc_mem(void);
t_size							get_malloc_type(size_t size);
size_t							get_page_size(size_t size);
t_page							**get_head_page_type(t_size type);
void							add_page(t_page *page);
size_t							get_page_size(size_t size);
t_page							*get_new_page(size_t size);
t_block							*insert_block_in_page(t_page *page,\
													size_t size);
t_block							*get_new_block(size_t size);
int								check_adress(void *adress);
void							defragment(void);
void							ft_putchar_fd(char c, int fd);
void							ft_putstr_fd(char *str, int fd);
void							ft_putnbr_fd(int n, int fd);
void							ft_fdprint(int fd, const char *fmt, ...);
void							ft_print(const char *fmt, ...);
void							*ft_memcpy(void *dest,\
											const void *src, size_t n);
void							ft_bzero(void *s, size_t n);

void							init_main_struct(void);
t_block							*get_free_block_in_list(size_t size);

#endif
