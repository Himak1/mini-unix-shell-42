/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envv_search.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 16:16:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/29 11:43:30 by jhille        ########   odam.nl         */
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
		if (!ft_strncmp(str, str_arr[i], ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_get_index(char **str_arr, char *str)
{
	int		i;
	char	**key_and_val;

	i = 0;
	while (str_arr[i] != NULL)
	{
		if (ft_strchr(str_arr[i], '='))
		{
			key_and_val = ft_split(str_arr[i], '=');
			if (!ft_strncmp(str, key_and_val[0], ft_strlen(key_and_val[0])))
			{
				ft_free_2d_array(key_and_val);
				return (i);
			}
			ft_free_2d_array(key_and_val);
		}
		if (!ft_strncmp(str, str_arr[i], ft_strlen(str_arr[i])))
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
