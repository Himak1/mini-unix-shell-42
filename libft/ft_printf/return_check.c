/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   return_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/13 20:14:40 by jhille        #+#    #+#                 */
/*   Updated: 2021/03/02 20:29:56 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	return_check(const char **format, char **store, int *pos, int *i)
{
	if (*pos == -2)
		*pos = 0;
	if (*pos != -1 && (*format)[*pos] != '\0')
		ft_skipchar(*format, pos);
	if (*store == 0 || *pos == -1)
		*i = -1;
	if (*store != 0)
		ft_resetptr((void **)store);
	if (*pos != -1)
		*format = (*format) + *pos;
}
