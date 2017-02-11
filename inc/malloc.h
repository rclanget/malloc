#ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>

# define MMAP_FLAG		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON

# define PAGESIZE   	(getpagesize())
# define ROUNDUP(x)     ((((x) + PAGESIZE - 1) / PAGESIZE) * PAGESIZE)

# define TINY_SIZE		(PAGESIZE / 16)
# define SMALL_SIZE 	(PAGESIZE / 4)

typedef	enum		e_type
{
	TINY = 1,
	SMALL = 2,
	LARGE = 3
}					t_type;

typedef struct		s_large
{
	size_t			size;
	struct s_large	*next;
	char			ptr;
}					t_large;

typedef struct		s_block
{
	int				is_free;
	t_type			type;
	struct s_block	*next;
	char			ptr;
}					t_block;


typedef struct		s_page
{
	size_t			size;
	t_type			type;
	t_block			*block;
	struct s_page	*next;
}					t_page;


typedef struct		s_main
{
	t_large			*large;
}					t_main;

void				*malloc(size_t size);
void				free(void *ptr);

t_main				*ft_singleton(void);
void				ft_bzero(void *p, size_t n);

int					ft_fprintf(int fd, char const *format, ...);

#endif