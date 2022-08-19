/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_index_2d.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 16:16:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/18 16:05:22 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_get_index_2d(char **str_arr, char *str)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		if (ft_strnstr(str_arr[i], str, ft_strlen(str_arr[i])) != NULL)
			return (i);
		i++;
	}
	return (0);
}
