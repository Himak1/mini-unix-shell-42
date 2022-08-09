/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 13:30:45 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:45:21 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dest, const void *source, int c, size_t num)
{
	size_t			i;
	unsigned char	*destptr;
	unsigned char	*sourceptr;

	i = 0;
	destptr = (unsigned char *)dest;
	sourceptr = (unsigned char *)source;
	while (i < num)
	{
		destptr[i] = (unsigned char)sourceptr[i];
		if (sourceptr[i] == (unsigned char)c)
			return (&destptr[i + 1]);
		i++;
	}
	return (NULL);
}
