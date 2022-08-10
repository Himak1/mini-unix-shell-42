/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 19:50:45 by jhille        #+#    #+#                 */
/*   Updated: 2021/03/02 21:01:52 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int	printlen(const char *str, int len, va_list args, t_strct *lst)
{
	int	ret;
	int	compare;

	ret = 0;
	compare = len;
	while (str[len] != '\0')
	{
		if (str[len] == '%')
			ret = varcheck(str, len + 1, args, lst);
		if (ret == -1)
			return (-1);
		else if (ret == 1)
			break ;
		len++;
	}
	if (compare == len)
		len = -2;
	return (len);
}

void	ft_skipchar(const char *format, int *pos)
{
	*pos += 1;
	while (ft_strchr(CONVS, format[*pos]) == 0 && format[*pos] != '\0')
		*pos += 1;
	*pos += 1;
}

static char	*store_join(char *store, t_strct *lst, va_list args)
{
	char	*temp1;
	int		len;

	temp1 = varjoin(lst, args);
	if (store != 0)
		len = ft_strlen(store);
	else
		len = 0;
	if (temp1 != 0 && store != 0)
	{
		store = ft_strrealloc(store, len + lst->width);
		if (store != 0)
			ft_memcpy(store + len, temp1, lst->width);
		free(temp1);
		lst->width += len;
	}
	else if (temp1 != 0)
		store = temp1;
	if (temp1 == 0 && store != 0)
		ft_resetptr((void **)&store);
	return (store);
}

int	ft_vfprintf(const char *format, va_list args)
{
	int				i;
	int				pos;
	char			*store;
	struct s_trct	lst;

	i = 0;
	store = 0;
	while (format[0] != '\0' && i != -1)
	{
		strctzero(&lst);
		pos = printlen(format, 0, args, &lst);
		if (pos > 0)
			store = ft_substr(format, 0, pos);
		if (pos > 0 && store == 0)
			return (-1);
		if ((pos != -1 && format[pos] == '%') || pos == -2)
			store = store_join(store, &lst, args);
		else if (pos != -1 && store != 0)
			lst.width = ft_strlen(store);
		if (pos != -1)
			i = write_check(store, lst.width, i);
		return_check(&format, &store, &pos, &i);
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		ret;
	va_list	args;

	if (format == 0)
		return (-1);
	va_start(args, format);
	ret = ft_vfprintf(format, args);
	va_end(args);
	return (ret);
}
