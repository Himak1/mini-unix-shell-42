/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 11:20:42 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/23 19:43:40 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// int	ft_strncmp(const char *str1, const char *str2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	if (str1[i] == '\0' || str2[i] == '\0')
// 	{
// 		if (str1[i] == '\0' && str2[i] == '\0')
// 			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
// 		else
// 			return ((unsigned char)str1[i - 1] - (unsigned char)str2[i - 1]);
// 	}
// 	while ((i < n - 1) && (str1[i] != '\0' && str2[i] != '\0'))
// 	{
// 		if (str1[i] != str2[i])
// 			break ;
// 		i++;
// 	}
// 	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
// }
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((unsigned char)s1[i] != '\0'
			|| (unsigned char)s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}