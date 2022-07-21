/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 14:46:12 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/20 14:46:53 by jhille        ########   odam.nl         */
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