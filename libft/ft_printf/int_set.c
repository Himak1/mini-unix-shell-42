/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   int_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 17:33:09 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/26 00:34:07 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	digits(int val)
{
	int	ndigit;

	ndigit = 0;
	if (val < 0)
		val *= -1;
	while (val > 0)
	{
		val /= 10;
		ndigit++;
	}
	return (ndigit);
}

static char	*negative_set(char *ret, t_strct *lst, int val)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(ret);
	lst->prec = lst->prec;
	while (ft_isdigit(ret[i]) == 0)
		i++;
	if (i == 0)
	{
		if (digits(val) >= len || lst->prec >= len)
			ret = width_correct(ret, 'z', len, len + 1);
		else if (ret[len - 2] == ' ')
			ft_memmove(&ret[1], ret, digits(val));
		if (ret != 0)
			ret[i] = '-';
	}
	else
		ret[i - 1] = '-';
	return (ret);
}

char	*int_set(t_strct *lst, va_list args)
{
	char	*ret;
	int		len;
	int		val;

	val = va_arg(args, int);
	if (val < 0)
		ret = ft_itoa(val * -1);
	else if (val > 0 || (val == 0 && lst->prec != 0))
		ret = ft_itoa(val);
	else
		ret = ft_calloc(1, 1);
	if (ret == 0)
		return (0);
	len = ft_strlen(ret);
	if (lst->prec > len)
		ret = width_correct(ret, '0', len, lst->prec);
	else if (lst->width > len && !(lst->width <= len + 1 && val < 0))
		ret = width_correct(ret, lst->flags, len, lst->width);
	if (ret != 0 && val < 0)
		ret = negative_set(ret, lst, val);
	if (ret != 0 && lst->width > (int)ft_strlen(ret))
		ret = width_correct(ret, lst->flags, ft_strlen(ret), lst->width);
	return (ret);
}

char	*uint_set(t_strct *lst, va_list args)
{
	char			*ret;
	unsigned int	val;
	int				len;

	val = va_arg(args, unsigned int);
	if (val == 0 && lst->prec == 0)
		ret = ft_calloc(1, 1);
	else
		ret = ft_uitoa(val);
	if (ret == 0)
		return (0);
	len = ft_strlen(ret);
	if (lst->prec > len)
		ret = width_correct(ret, '0', len, lst->prec);
	else if (lst->width > len && lst->prec == -1)
		ret = width_correct(ret, lst->flags, len, lst->width);
	if (ret != 0 && lst->width > (int)ft_strlen(ret))
		ret = width_correct(ret, lst->flags, ft_strlen(ret), lst->width);
	return (ret);
}
