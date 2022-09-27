/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_index_key.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 16:16:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/26 14:30:44 by tvan-der      ########   odam.nl         */
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
			&& !ft_strncmp(str, str_arr[i], ft_strlen(str_arr[i])))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char *envv[], char *var_name)
{
	int	index;

	index = ft_get_index_key(envv, var_name);
	if (index == -1)
		return (NULL);
	return (envv[index]);
}