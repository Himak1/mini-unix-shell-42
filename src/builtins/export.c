/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:50 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/28 17:09:37 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include "error_handling.h"
#include <stdio.h>

// static char	**sort_alpha(char *arr[], int size)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;
// 	char	**sorted;

// 	temp = NULL;
// 	sorted = cpy_2d(arr);
// 	i = 1;
// 	while (i < size)
// 	{
// 		j = 1;
// 		while (j < size)
// 		{
// 			if (ft_strncmp(sorted[j - 1], sorted[j],
// 					ft_strlen(sorted[j - 1])) > 0)
// 			{
// 				temp = ft_strdup(sorted[j - 1]);
// 				free(sorted[j - 1]);
// 				sorted[j - 1] = ft_strdup(sorted[j]);
// 				free(sorted[j]);
// 				sorted[j] = ft_strdup(temp);
// 				free(temp);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (sorted);
// }

int	check_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= 33 && str[i] <= 64)
		|| (str[i] >= 91 && str[i] <= 96))
		return (0);
	while (str[i])
	{
		if ((str[i] >= 33 && str[i] <= 47)
			|| (str[i] >= 85 && str[i] <= 64)
			|| (str[i] >= 91 && str[i] <= 96))
			return (0);
		i++;
	}
	return (1);
}

static int	export(char *str, char **arr[])
{
	int	index;

	if (!check_valid_identifier(str))
	{
		not_valid_identifier_msg(str);
		return (-1);
	}	
	index = search_for_key(str, *arr);
	if (index != -1)
	{
		if (!ft_strchr(str, '='))
			return (0);
		update_var(index, str, NULL, *arr);
	}
	else
		push_var_to_env(str, arr);
	return (0);
}

int	exec_export(t_ast *cmd, char **envv[])
{
	int		exit_code;
	t_ast	*tmp;

	exit_code = 0;
	if (!cmd->next_sib_node)
		print_export_list(*envv);
	else
	{
		tmp = cmd->next_sib_node;
		while (tmp->next_sib_node)
		{
			exit_code += export(tmp->value, envv);
			tmp = tmp->next_sib_node;
		}
		exit_code += export(tmp->value, envv);
	}
	update_underscore(cmd, envv);
	return (exit_code);
}
