/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:19:13 by jhille        #+#    #+#                 */
/*   Updated: 2021/11/21 22:37:32 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (needle[k] != '\0')
		k++;
	while (haystack[i] != '\0' && i < len)
	{
		if (j == k)
			return ((char *)&haystack[i - j]);
		if (haystack[i] == needle[j])
			j++;
		else if (haystack[i] == needle[0])
			j = 1;
		else
			j = 0;
		i++;
	}
	if (j == k)
		return ((char *)&haystack[i - j]);
	else
		return (NULL);
}
