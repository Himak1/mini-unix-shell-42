/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 00:02:57 by jhille        #+#    #+#                 */
/*   Updated: 2020/11/25 21:07:52 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	j;
	char			*ret;

	if (str == 0 || f == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j] != '\0')
		j++;
	ret = malloc(j + 1 * sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (i < j)
	{
		ret[i] = (*f)(i, str[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
