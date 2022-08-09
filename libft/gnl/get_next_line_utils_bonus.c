/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 11:12:13 by jhille        #+#    #+#                 */
/*   Updated: 2021/11/21 23:04:21 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

void	*ft_gnl_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ret;
	size_t			i;

	i = 0;
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	ret = (unsigned char *)malloc(nmemb * size);
	if (ret == NULL)
		return (NULL);
	while (i < (nmemb * size))
	{
		ret[i] = 0;
		i++;
	}
	return ((void *)ret);
}

char	*gnl_substr(char *str, unsigned int start, size_t len)
{
	size_t		i;
	char		*ret;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (len == 0 && str[0] != '\n')
		len += 1;
	if (start > (size_t)linelen(str, 2))
		return (ft_gnl_calloc(1, 1));
	if (len > (size_t)linelen(str, 2) - start)
		len = (size_t)linelen(str, 2) - start;
	ret = (char *)ft_gnl_calloc((len + 1), sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	return (ret);
}

int	linelen(char *str, int returntype)
{
	int	len;
	int	mode;

	len = 0;
	mode = 0;
	while ((str[len] != '\0') && (str[len] != '\n'))
		len++;
	if (returntype == 2)
	{
		while (str[len] != '\0')
			len++;
	}
	else if (str[len] == '\n' && str[len + 1] == '\0')
		mode = 0;
	else if (str[len] == '\n')
		mode = 1;
	else if (str[len] == '\0')
		mode = 2;
	if (returntype == 0)
		returntype = mode;
	else if (returntype == 1 || returntype == 2)
		returntype = len;
	return (returntype);
}

void	ft_setzero(void *dest, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		*(ptr + i) = '\0';
		i++;
	}
}

char	*ft_gnl_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	int		retlen;
	char	*ret;

	i = 0;
	j = 0;
	if (str1 == 0 || str2 == 0)
		return (NULL);
	retlen = (size_t)linelen(str1, 2) + (size_t)linelen(str2, 2) + 1;
	ret = (char *)ft_gnl_calloc(retlen + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (str1[i] != '\0')
	{
		ret[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		ret[i] = str2[j];
		i++;
		j++;
	}
	return (ret);
}
