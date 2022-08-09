/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basic_sets.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 18:20:08 by jhille        #+#    #+#                 */
/*   Updated: 2021/03/28 21:01:00 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char	*char_set(t_strct *lst, va_list args)
{
	char	*ret;

	ret = ft_calloc(2, 1);
	if (ret != 0)
		ret[0] = va_arg(args, int);
	if (ret != 0 && lst->width != 0)
		ret = width_correct(ret, lst->flags, 1, lst->width);
	if (ret != 0 && lst->width == 0)
		lst->width = 1;
	return (ret);
}

char	*str_set(t_strct *lst, va_list args)
{
	char		*ret;
	char		*val;
	int			len;

	val = va_arg(args, char *);
	if (val == 0)
		ret = ft_strdup("(null)");
	else
		ret = ft_strdup(val);
	if (ret == 0)
		return (0);
	len = ft_strlen(ret);
	if (lst->flags == '0')
		lst->flags = 0;
	if (lst->prec < len && lst->prec > -1)
		ret = width_correct(ret, 'z', len, lst->prec);
	if (lst->width > (int)ft_strlen(ret))
		ret = width_correct(ret, lst->flags, (int)ft_strlen(ret), lst->width);
	return (ret);
}

char	*percent_set(char c, t_strct *lst)
{
	char	*ret;

	ret = ft_calloc(2, 1);
	if (ret == 0)
		return (0);
	ret[0] = c;
	if (lst->width > 1)
		ret = width_correct(ret, lst->flags, 1, lst->width);
	return (ret);
}

char	*width_correct(char *ret, char flag, int olen, int nlen)
{
	char	c;

	if (flag == '0')
		c = '0';
	else
		c = ' ';
	ret = ft_strrealloc(ret, nlen);
	if (flag != '-' && nlen > olen && ret != 0)
	{
		ft_memmove(&ret[nlen - olen], ret, olen);
		ft_memset((void *)ret, c, nlen - olen);
	}
	else if (nlen > olen && ret != 0)
	{
		ft_memset((void *)&ret[olen], c, nlen - (olen));
	}
	return (ret);
}

char	*varjoin(t_strct *lst, va_list args)
{
	char	*var;

	var = 0;
	if (lst->conv == 'c')
		var = char_set(lst, args);
	else if (lst->conv == 's')
		var = str_set(lst, args);
	else if (lst->conv == 'p')
		var = ptr_set(lst, args);
	else if (lst->conv == 'd' || lst->conv == 'i')
		var = int_set(lst, args);
	else if (lst->conv == 'u')
		var = uint_set(lst, args);
	else if (lst->conv == 'x' || lst->conv == 'X')
		var = hexstr_set(lst, args);
	else if (lst->conv == '%')
		var = percent_set(lst->conv, lst);
	if (lst->conv != 'c' && var != 0)
		lst->width = ft_strlen(var);
	return (var);
}
