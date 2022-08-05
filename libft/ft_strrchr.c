/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:05:00 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:49:14 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	charac;
	char	*strptr;

	i = 0;
	strptr = (char *)str;
	charac = (char)c;
	while (strptr[i] != '\0')
		i++;
	while (i != 0)
	{
		if (strptr[i] == charac)
			return (&strptr[i]);
		i--;
	}
	if (strptr[i] == charac)
		return (&strptr[i]);
	else
		return (NULL);
}
