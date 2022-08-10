/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 21:51:19 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/26 18:42:06 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	write_check(char *store, int len, int i)
{
	int	ret;

	ret = 0;
	if (store != 0)
		ret = write(1, store, len);
	if (ret != -1)
		ret += i;
	return (ret);
}
