/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_2d_array.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 16:16:00 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/18 13:17:47 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**ft_free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
