/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cpy.2d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 11:53:43 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/19 11:54:34 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

char **cpy_2d(char **arr)
{
    int size;
    char **new_arr;
    
    size = 0;
    while (arr[size])
        size++;
    new_arr = ft_xmalloc(sizeof(char *) * (size + 1));
    size = 0;
    while (arr[size])
	{
		new_arr[size] = ft_strdup(arr[size]);
		if (!new_arr[size])
			exit(EXIT_FAILURE);
		size++;
	}
	new_arr[size] = NULL;
    return (new_arr);
}