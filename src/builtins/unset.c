/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:58 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/23 15:25:47 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "error_handling.h"
#include "builtins.h"
#include <stdio.h>

void	print_envp(char **envp) //delete
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static	int unset(char *str, char **arr[])
{
	int	index;

	if (!check_valid_identifier(str))
	{
		not_valid_identifier_msg(str);
		return (-1);
	}	
	index = search_for_key(str, *arr);
	if (index != -1)
		pop_var_from_env(str, arr);
	return (0);
}

int	exec_unset(t_ast *cmd, char **envv[])
{
	int		exit_code;
	t_ast	*tmp;

	exit_code = 0;
	if (cmd->next_sib_node)
	{
		tmp = cmd->next_sib_node;
		while (tmp->next_sib_node)
		{
			//printf("hello");
			exit_code += unset(tmp->value, envv);
			tmp = tmp->next_sib_node;
		}
	exit_code += unset(tmp->value, envv);
	}
	update_underscore(cmd, envv);
	return (exit_code);
}