/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 15:54:22 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/13 15:54:41 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		len;

	len = ft_strlen(s1);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	else
		ft_strlcpy(ptr, s1, (len + 1));
	return (ptr);
}