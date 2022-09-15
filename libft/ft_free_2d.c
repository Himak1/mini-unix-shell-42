/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_2d.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 22:38:33 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/14 16:26:29 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_2d(char *two_d_array[])
{
	int	i;

	i = 0;
	while (two_d_array[i] != 0)
	{
		free(two_d_array[i]);
		i++;
	}
}
