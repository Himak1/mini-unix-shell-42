/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hex_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 18:20:22 by jhille        #+#    #+#                 */
/*   Updated: 2021/03/03 12:42:49 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	arraylen(long long convert)
{
	int	i;

	i = 0;
	while (convert > 0)
	{
		convert /= 16;
		i++;
	}
	return (i);
}

char	*hex_set(long long convert, int letcase)
{
	char	*ret;
	int		i;

	i = arraylen(convert) - 1;
	if (i == -1)
		i = 0;
	ret = ft_calloc(i + 2, 1);
	while (i > -1 && ret != 0)
	{
		if (convert % 16 < 10)
			ret[i] = (convert % 16) + 48;
		else
			ret[i] = (convert % 16) + 55 + letcase;
		convert /= 16;
		i--;
	}
	return (ret);
}

char	*ptr_set(t_strct *lst, va_list args)
{
	char			*ret;
	char			*temp;
	int				len;
	unsigned long	val;

	val = va_arg(args, unsigned long);
	if (val != 0 || (val == 0 && lst->prec != 0))
		temp = hex_set(val, 32);
	else
		temp = ft_calloc(1, 1);
	if (temp == 0)
		return (0);
	if (temp != 0)
	{
		ret = ft_strjoin("0x", temp);
		free(temp);
	}
	else
		ret = temp;
	len = ft_strlen(ret);
	if (lst->width > len)
		ret = width_correct(ret, lst->flags, len, lst->width);
	return (ret);
}

char	*hexstr_set(t_strct *lst, va_list args)
{
	char			*ret;
	int				len;
	unsigned int	val;

	val = va_arg(args, unsigned int);
	if (lst->conv == 'X')
		ret = hex_set(val, 0);
	else
		ret = hex_set(val, 32);
	if (ret == 0)
		return (0);
	len = ft_strlen(ret);
	if ((lst->prec < len && lst->prec != -1) && (ret[0] == '0' && len == 1))
		ret = width_correct(ret, 'z', len, lst->prec);
	else if (lst->prec > len)
		ret = width_correct(ret, '0', len, lst->prec);
	if (ret != 0 && lst->width > (int)ft_strlen(ret))
		ret = width_correct(ret, lst->flags, (int)ft_strlen(ret), lst->width);
	return (ret);
}
