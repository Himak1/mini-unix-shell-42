/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 14:24:28 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/19 16:11:27 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "builtins.h"
#include "minishell.h"
#include <stdio.h>

int	is_builtin(t_ast *exec_block, t_uint cmd_count)
{
	int is_builtin;
	t_ast *iter;

	is_builtin = 0;
	iter = exec_block->child_node;
	if (iter->type != CMD)
		iter = iter->next_sib_node;
	iter = iter->child_node;
	if (cmd_count == 1 && !ft_strncmp(iter->value, "echo", ft_strlen(iter->value)))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "cd", ft_strlen(iter->value)))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "pwd", ft_strlen(iter->value)))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "env", ft_strlen(iter->value)))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "export", ft_strlen(iter->value)))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "unset", ft_strlen(iter->value)))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "exit", ft_strlen(iter->value)))
		return (1);
	return (0);
}

int exec_builtin(t_ast *exec_block, char *envp[])
//return value void or int???? 
{
	t_ast *iter;

	iter = exec_block->child_node;
	if (iter->type != CMD)
		iter = iter->next_sib_node;
	iter = iter->child_node; //terminal
	if (!ft_strncmp(iter->value, "echo", ft_strlen(iter->value)))
		return (exec_echo(iter, envp));
	if (!ft_strncmp(iter->value, "cd", ft_strlen(iter->value)))
		return (exec_cd(iter, envp));
	if (!ft_strncmp(iter->value, "pwd", ft_strlen(iter->value)))
		return (exec_pwd(iter, envp));
	if (!ft_strncmp(iter->value, "env", ft_strlen(iter->value)))
		return (exec_env(iter, envp));
	// if (!ft_strncmp(iter->value, "export", ft_strlen(iter->value)))
	// 	return (exec_export(iter, envp));
	// if (!ft_strncmp(iter->value, "unset", ft_strlen(iter->value)))
	// 	return (exec_unset(iter, envp));
	// if (!ft_strncmp(iter->value, "exit", ft_strlen(iter->value)))
	// 	return (exec_exit(iter, envp));
	return (1); //error
}