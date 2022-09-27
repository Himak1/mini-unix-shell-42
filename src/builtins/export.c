/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:50 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/26 14:34:38 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include "error_handling.h"
#include <stdio.h>

static char	**sort_alpha(char *arr[], int size)
{
	int		i;
	int		j;
	char	*temp;
	char	**sorted;

	temp = NULL;
	sorted = cpy_2d(arr);
	i = 1;
	while (i < size)
	{
		j = 1;
		while (j < size)
		{
			if (ft_strncmp(sorted[j - 1], sorted[j],
					ft_strlen(sorted[j - 1])) > 0)
			{
				temp = ft_strdup(sorted[j - 1]);
				free(sorted[j - 1]);
				sorted[j - 1] = ft_strdup(sorted[j]);
				free(sorted[j]);
				sorted[j] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

void	print_with_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
	if (!str[i])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	ft_putchar_fd(str[i], STDOUT_FILENO);
	i++;
	ft_putchar_fd('"', STDOUT_FILENO);
	while (str[i] && str[i] != '=')
	{
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	print_export_list(char *envv[])
{
	int		envv_size;
	char	**sorted_envv;

	envv_size = 0;
	while (envv[envv_size])
		envv_size++;
	sorted_envv = sort_alpha(envv, envv_size);
	envv_size = 0;
	while (sorted_envv[envv_size])
	{
		if (ft_strncmp(sorted_envv[envv_size], "_=", ft_strlen("_=")))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			print_with_quotes(sorted_envv[envv_size]);
		}
		envv_size++;
	}
	ft_free_2d_array(sorted_envv);
}

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
