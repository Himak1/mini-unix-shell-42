/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 10:39:53 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/26 13:01:43 by tvan-der      ########   odam.nl         */
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
		i = ft_get_index_key(arr, key_and_val[0]);
		if (!ft_strncmp(arr[i], key_and_val[0], ft_strlen(key_and_val[0])))
		{
			ft_free_2d_array(key_and_val);
			return (i);
		}
	}
	i = ft_get_index_key(arr, key);
	printf("i = %d\n", i);
	if (!ft_strncmp(arr[i], key, ft_strlen(key)))
		return (i);
	return (-1);
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

void pop_var_from_env(char *str, char **arr[])
{
    int i;
    int j;
    int index;
    int size;
    char **temp;
    char **new_arr;

    index = 0;
    temp = *arr;
    size = 0;
    while (temp[size])
        size++;
    while (temp[index])
    {
        if (ft_strnstr(temp[index], str, ft_strlen(str)))
            break;
        index++;
    }
    if (index == size && ft_strncmp(temp[index], str, ft_strlen(str)))
        return ;
    new_arr = ft_xmalloc(sizeof(char *) * size);
    i = 0;
    j = 0;
    while (j < size && temp[i])
    {
        if (i == index)
            i++;
        if (temp[i])
        {
            new_arr[j] = ft_strdup(temp[i]);
            i++;
            j++;
        }
    }
    new_arr[j] = NULL;
    ft_free_2d_array(*arr);
    *arr = new_arr;
}
