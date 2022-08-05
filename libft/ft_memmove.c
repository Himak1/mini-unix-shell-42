/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 13:37:05 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/21 23:45:59 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static	int	chkoverlap(unsigned char *dest, unsigned char *src, size_t n)
{
	size_t	j;

	j = 0;
	while (j < n)
	{
		if ((dest + 0) == (src + j))
			return (1);
		j++;
	}
	return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	iter;

	i = 0;
	iter = n - 1;
	if (dest == 0 && src == 0)
		return (NULL);
	if (chkoverlap((unsigned char *)dest, (unsigned char *)src, n) == 1)
	{
		while (iter < n)
		{
			*(unsigned char *)(dest + iter) = *(unsigned char *)(src + iter);
			iter--;
		}
		return (dest);
	}
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}
