/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:50 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/29 10:53:41 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include "error_handling.h"
#include <stdio.h>

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
	sorted_envv = sort_2d_alpha(envv, envv_size);
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
	printf("found at index %d\n", index);
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
