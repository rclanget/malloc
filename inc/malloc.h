#ifndef MALLOC_H
# define MALLOC_H

#include <stdio.h>

#define GETPAGESIZE		(getpagesize())
#define ROUNDUP(x)		(((x + GETPAGESIZE - 1) / GETPAGESIZE) * GETPAGESIZE)

# define OFFSETOF(type, member) ((size_t) &((type *)0)->member)
# define CONTAINEROF(ptr, t, m) ((t *)((char *)(ptr) - OFFSETOF(t, m)))


struct				s_page;

typedef struct		s_block
{
	size_t			size;
	int				is_free;
	struct s_page	*parent_page;
	struct s_block	*next;
	struct s_block	*prev;
	struct s_block	*free_next;
	struct s_block	*free_prev;
}					t_block;

typedef enum		e_size
{
	TINY = 1,
	SMALL = 2,
	LARGE = 3
}					t_size;

typedef struct		s_page
{
	t_size			type;
	size_t			size;
	size_t			free_mem;
	t_block			*block_list;
	struct s_page	*next;
	struct s_page	*prev;
}					t_page;

typedef struct		s_main
{
	int				init;
	t_page			*page;
	t_block			*free_block;
}					t_main;

t_main				*g_main_struct;

void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);
size_t				get_page_size(size_t size);
t_page				**get_head_page_type(t_size type);

void				add_page(t_page *page);
size_t				get_page_size(size_t size);
t_page				*get_new_page(size_t size);

t_block				*insert_block_in_page(t_page *page, size_t size);
t_block				*get_new_block(size_t size);

void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_bzero(void *s, size_t n);

#endif
