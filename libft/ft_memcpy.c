/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 13:34:19 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:46:14 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *source, size_t num)
{
	size_t			i;
	unsigned char	*destptr;
	unsigned char	*sourceptr;

	i = 0;
	destptr = (unsigned char *)dest;
	sourceptr = (unsigned char *)source;
	if (destptr == 0 && sourceptr == 0)
		return (0);
	while (i < num)
	{
		destptr[i] = sourceptr[i];
		i++;
	}
	return (dest);
}
