#include "ft_utils.h"

void	ft_memcpy(void *dest, const void *src, int n)
{
	int	i;

	if (!dest || !src || n <= 0)
		return ;
	i = -1;
	while (++i < n)
		*(char *)(dest + i) = *(char *)(src + i);
}