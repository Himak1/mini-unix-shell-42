/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 11:20:42 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/26 14:10:00 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (str1[i] == '\0' || str2[i] == '\0')
	{
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	while ((i < n - 1) && (str1[i] != '\0' && str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
