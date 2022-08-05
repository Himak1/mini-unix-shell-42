/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   varcheck_states.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 18:20:32 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/26 00:34:33 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_width_prec(const char *format, int startnum, int endnum)
{
	int		ret;
	char	temp[11];

	temp[endnum - startnum] = '\0';
	ft_strlcpy(temp, &format[startnum], (endnum - startnum) + 1);
	ret = ft_atoi(temp);
	return (ret);
}

int	struct_set(const char *str, int *parameter, int *len)
{
	*parameter = *len;
	while (ft_isdigit(str[*len]) != 0)
		*len += 1;
	if ((*len - *parameter) > 10)
		return (-1);
	if (*parameter != *len)
		*parameter = get_width_prec(str, *parameter, *len);
	else
		*parameter = 0;
	return (0);
}

void	arg_set(const char *str, int *strct_int, int *len, va_list args)
{
	*strct_int = va_arg(args, int);
	if (str[*len + 1] != '\0')
		*len += 1;
	if (str[*len] == '*')
	{
		*len += 1;
	}
}

void	flag_set(const char *str, int *len, t_strct *lst)
{
	if (str[*len] == '-' || str[*len] == '0')
	{
		if (str[*len] == '\0')
			return ;
		else if (str[*len] == '-' || str[*len] == '0')
		{
			lst->flags = str[*len];
			*len += 1;
		}
		while ((str[*len] == '0' || str[*len] == '-') && str[*len] != '\0')
		{
			*len += 1;
			if (str[*len] == '-')
				lst->flags = '-';
		}
	}
}
