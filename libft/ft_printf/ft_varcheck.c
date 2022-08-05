/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_varcheck.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/05 21:02:22 by jhille        #+#    #+#                 */
/*   Updated: 2021/03/04 15:54:32 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	negative_width(t_strct *lst)
{
	if (lst->width < 0)
	{
		lst->flags = '-';
		lst->width *= -1;
	}
}

static int	prec_set(const char *str, t_strct *lst, int *len)
{
	*len += 1;
	return (struct_set(str, &lst->prec, len));
}

int	varcheck(const char *str, int len, va_list args, t_strct *lst)
{
	int	ret;

	ret = 0;
	flag_set(str, &len, lst);
	if (str[len] == '*')
		arg_set(str, &lst->width, &len, args);
	else if (ft_isdigit(str[len]) != 0)
		ret = struct_set(str, &lst->width, &len);
	if (str[len] == '.' && str[len + 1] != '*')
		ret = prec_set(str, lst, &len);
	else if (str[len] == '.' && str[len + 1] == '*')
		arg_set(str, &lst->prec, &len, args);
	if (ft_strchr(CONVS, str[len]) != 0)
		lst->conv = str[len];
	negative_width(lst);
	if (lst->prec > -1 && lst->flags == '0')
		lst->flags = 0;
	if (lst->conv != 0 && ret != -1)
		return (1);
	else if (lst->conv != 0 && ret == -1)
		return (-1);
	return (0);
}
