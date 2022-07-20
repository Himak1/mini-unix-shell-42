/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_array.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 16:42:35 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/07 16:49:31 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_array(void **ptr_array, const int array_len)
{
	int	i;

	i = 0;
	while (i < array_len)
	{
		free(ptr_array[i]);
		ptr_array[i] = 0;
		i++;
	}
}
