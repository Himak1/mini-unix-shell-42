/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_index_key.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 16:16:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/21 09:24:13 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdio.h>

int	ft_get_index_key(char **str_arr, char *str)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		if (ft_strnstr(str_arr[i], str, ft_strlen(str_arr[i])) != NULL
			&& !ft_strncmp(str, str_arr[i], ft_strlen(str)))
			return (i);
		i++;
	}
	return (0);
}

// int	ft_get_index_key(char **str_arr, char *str)
// {
// 	int	i;
// 	char **temp;

// 	i = 0;
// 	temp = NULL;
// 	while (str_arr[i] != NULL)
// 	{
// 		if (ft_strchr(str_arr[i], '='))
// 		{
// 			temp = ft_split(str_arr[i], '=');
// 			if (ft_strnstr(temp[0], str, ft_strlen(temp[0])) != NULL
// 				&& !ft_strncmp(temp[0], str, ft_strlen(temp[0])))
// 			{
// 				printf("temp[0] = %s\n", temp[0]);
// 				ft_free_2d_array(temp);
// 				return (i);
// 			}
// 			ft_free_2d_array(temp);
// 		}
// 		else
// 		{
// 			if (ft_strnstr(str_arr[i], str, ft_strlen(str_arr[i])) != NULL
// 				&& !ft_strncmp(str_arr[i], str, ft_strlen(str)))
// 				return (i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }
