/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 17:05:06 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/01 13:18:58 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
