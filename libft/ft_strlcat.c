/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 16:17:43 by jhille        #+#    #+#                 */
/*   Updated: 2020/11/25 21:04:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (dest[i] != '\0' && i < destsize)
		i++;
	len = i;
	while (i < destsize && src[j] != '\0')
	{
		if (i < destsize - 1)
			dest[i] = src[j];
		j++;
		i++;
		if (i == destsize - 1)
			dest[i] = '\0';
	}
	if (i == destsize - 1 || src[j] == '\0')
		dest[i] = '\0';
	return (ft_strlen(src) + len);
}
