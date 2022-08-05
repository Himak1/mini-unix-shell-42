/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:42:28 by jhille        #+#    #+#                 */
/*   Updated: 2021/03/30 11:27:58 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arraylen(unsigned int convert, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (convert > 0)
	{
		convert /= 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}

static void	conversion(unsigned int convert, int i, int n, char *ret)
{
	while (convert > 0)
	{
		ret[i - 1] = (convert % 10) + 48;
		convert /= 10;
		i--;
	}
	i--;
	if (n < 0)
		ret[i] = '-';
}

char	*ft_itoa(int n)
{
	int				i;
	char			*ret;
	unsigned int	convert;

	if (n < 0)
		convert = n * -1;
	else
		convert = n;
	i = arraylen(convert, n);
	ret = ft_calloc(i + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	if (n == 0)
		ret[0] = 0 + 48;
	else
		conversion(convert, i, n, ret);
	return (ret);
}
