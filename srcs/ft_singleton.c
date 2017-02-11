#include "malloc.h"

t_main	*ft_singleton(void)
{
	static t_main *ptr;

	if (!ptr)
	{
		ptr = (t_main *)mmap(0, sizeof(t_main), MMAP_FLAG, -1, 0);
		if (ptr == MAP_FAILED)
			return (0);
		ft_bzero(ptr, sizeof(t_main));
	}
	return (ptr);
}