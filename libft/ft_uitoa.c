/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:42:28 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/21 23:47:18 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arraylen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	conversion(unsigned int convert, int i, char *ret)
{
	while (convert > 0)
	{
		ret[i - 1] = (convert % 10) + 48;
		convert /= 10;
		i--;
	}
}

char	*ft_uitoa(unsigned int n)
{
	int				i;
	char			*ret;

	i = arraylen(n);
	ret = ft_calloc(i + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	if (n == 0)
		ret[0] = 0 + 48;
	else
		conversion(n, i, ret);
	return (ret);
}
