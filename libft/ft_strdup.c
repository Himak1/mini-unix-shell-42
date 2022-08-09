/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 18:12:04 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:48:32 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*ret;
	int		i;
	int		strsize;

	i = 0;
	strsize = 0;
	while (str[strsize] != '\0')
		strsize++;
	strsize++;
	ret = (char *)malloc(strsize * sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (i < strsize)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}
