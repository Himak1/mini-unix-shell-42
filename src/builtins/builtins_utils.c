/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 10:39:53 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/27 14:42:09 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "builtins.h"
#include <stdio.h>

int	search_for_key(char *key, char **arr)
{
	int		i;
	char	**key_and_val;

	i = 0;
	if (ft_strchr(key, '='))
	{
		key_and_val = ft_split(key, '=');
		i = ft_get_index(arr, key_and_val[0]);
		ft_free_2d_array(key_and_val);
		if (i == -1)
			return (-1);
		return (i);
	}
	i = ft_get_index(arr, key);
	if (i == -1)
		return (-1);
	return (i);
}

void	push_var_to_env(char *str, char **arr[])
{
	int		i;
	char	**temp;
	char	**new_arr;

	i = 0;
	temp = *arr;
	while (temp[i] != NULL)
		i++;
	new_arr = ft_xmalloc(sizeof(char *) * (i + 2));
	i = 0;
	while (temp[i] != NULL)
	{
		new_arr[i] = ft_strdup(temp[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	i++;
	new_arr[i] = NULL;
	ft_free_2d_array(*arr);
	*arr = new_arr;
}

void	pop_var_from_env(char **arr[], int index)
{
	int		i;
	int		j;
	int		size;
	char	**new_arr;

	size = 0;
	while ((*arr)[size])
		size++;
	new_arr = ft_xmalloc(sizeof(char *) * size);
	i = 0;
	j = 0;
	while (j < size && (*arr)[i])
	{
		if (i == index)
			i++;
		if ((*arr)[i])
		{
			new_arr[j] = ft_strdup((*arr)[i]);
			i++;
			j++;
		}
	}
	new_arr[j] = NULL;
	ft_free_2d_array(*arr);
	*arr = new_arr;
}
