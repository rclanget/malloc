#include "malloc.h"

void	*ft_malloc_large(size_t size)
{
	t_large *new;
	size_t	total_size;

	total_size = ROUNDUP(size + sizeof(t_large));
	ft_fprintf(2, "size: %d\n", total_size);
	new = (t_large *)mmap(0, total_size, MMAP_FLAG, -1, 0);
	if (new)
	{
		new->size = total_size;
		new->next = ft_singleton()->large;
		ft_singleton()->large = new;
		return ((void *)&new->ptr);
	}
	return (0);
}

void	*ft_malloc(size_t size)
{
	// if (size > (int)SMALL_SIZE)
		return (ft_malloc_large(size));
}

void	*malloc(size_t size)
{
	void *ptr;

	// mutex ON
	ptr = ft_malloc(size);
	// mutex OFF
	return (ptr);
}