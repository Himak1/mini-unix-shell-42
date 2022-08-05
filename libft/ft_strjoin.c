/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:40:08 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:48:49 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	twostrlen(char const *str1, char const *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i] != '\0')
		i++;
	while (str2[j] != '\0')
		j++;
	return ((j + i) + 1);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	int		i;
	int		j;
	int		retlen;
	char	*ret;

	i = 0;
	j = 0;
	if (str1 == 0 || str2 == 0)
		return (NULL);
	retlen = twostrlen(str1, str2);
	ret = (char *)ft_calloc(retlen + 1, sizeof(char));
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
