/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 18:21:06 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:49:01 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	charac;
	char	*strptr;

	i = 0;
	strptr = (char *)str;
	charac = (char)c;
	while (strptr[i] != '\0')
	{
		if (strptr[i] == charac)
			return (&strptr[i]);
		i++;
	}
	if (strptr[i] == charac)
		return (&strptr[i]);
	else
		return (NULL);
}
