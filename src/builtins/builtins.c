/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 14:24:28 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/27 17:37:22 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "builtins.h"

int	is_builtin(t_ast *exec_block, t_uint cmd_count)
{
	t_ast	*iter;

	iter = exec_block->child_node;
	if (iter->type != CMD)
		iter = iter->next_sib_node;
	iter = iter->child_node;
	if (cmd_count == 1 && !ft_strncmp(iter->value, "echo", 5))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "cd", 3))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "pwd", 4))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "env", 4))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "export", 7))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "unset", 6))
		return (1);
	if (cmd_count == 1 && !ft_strncmp(iter->value, "exit", 5))
		return (1);
	return (0);
}

static int	exec_and_exit(t_ast *cmd, char **envv[],
	int (*f)(t_ast *cmd, char **envv[]))
{
	int	exit_code;

	exit_code = f(cmd, envv);
	if (exit_code >= 0)
		return (exit_code);
	return (EXIT_FAILURE);
}

int	exec_builtin(t_ast *exec_block, char **envv[])
{
	t_ast	*iter;

	iter = exec_block->child_node;
	if (iter->type != CMD)
		iter = iter->next_sib_node;
	iter = iter->child_node;
	if (!ft_strncmp(iter->value, "echo", 5))
		return (exec_echo(iter, envv));
	if (!ft_strncmp(iter->value, "cd", 3))
		return (exec_cd(iter, envv));
	if (!ft_strncmp(iter->value, "pwd", 4))
		return (exec_pwd(iter, envv));
	if (!ft_strncmp(iter->value, "env", 4))
		return (exec_env(iter, envv));
	if (!ft_strncmp(iter->value, "export", 7))
		return (exec_and_exit(iter, envv, exec_export));
	if (!ft_strncmp(iter->value, "unset", 6))
		return (exec_and_exit(iter, envv, exec_unset));
	if (!ft_strncmp(iter->value, "exit", 5))
		return (exec_exit(iter));
	return (1);
}
