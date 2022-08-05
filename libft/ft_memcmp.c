/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 13:42:41 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:45:53 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*str1ptr;
	unsigned char	*str2ptr;

	i = 0;
	str1ptr = (unsigned char *)str1;
	str2ptr = (unsigned char *)str2;
	while (i < n)
	{
		if (!(str1ptr[i] == str2ptr[i]))
			return ((unsigned char)str1ptr[i] - str2ptr[i]);
		i++;
	}
	return (0);
}
