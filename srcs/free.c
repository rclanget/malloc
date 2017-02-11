#include "malloc.h"

int		ft_free_large(void *ptr)
{
	t_large *large;
	t_large *prev;

	prev = 0;
	large = ft_singleton()->large;
	while (large)
	{
		if ((void *)&large->ptr == ptr)
		{
			if (!prev)
				ft_singleton()->large = large->next;
			else
				prev->next = large->next;
			munmap((void *)ptr, large->size);
			return (1);
		}
		prev = large;
		large = large->next;
	}
	return (0);
}

void	ft_free(void *ptr)
{
	if (ft_free_large(ptr))
		return ;
}

void	free(void *ptr)
{
	// mutex on
	ft_free(ptr);
	// mutex off
}