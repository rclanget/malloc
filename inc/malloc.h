#ifndef MALLOC_H
# define MALLOC_H

#include <stdlib.h>
#include <sys/mman.h>

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
	t_size			size;
	size_t			free_mem;
	t_block			*block_list;
	struct s_page	*next;
	struct s_page	*prev;
}					t_page;

typedef struct		s_main
{
	t_page			*tiny_page;
	t_page			*small_page;
	t_page			*large_page;
	t_block			*free_block;
}					t_main;

void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);

#endif
