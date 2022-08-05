/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 20:35:19 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:49:51 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t		i;
	char		*ret;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (start > ft_strlen(str))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(str) - start)
		len = ft_strlen(str) - start;
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
