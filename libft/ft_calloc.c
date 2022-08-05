/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 15:36:07 by jhille        #+#    #+#                 */
/*   Updated: 2021/11/21 22:38:20 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
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
