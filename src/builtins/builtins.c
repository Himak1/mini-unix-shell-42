/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 14:24:28 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/29 14:15:25 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "builtins.h"
#include "executor.h"

inline t_ast	*get_term(t_ast *exec_block)
{
	t_ast	*iter;

	iter = exec_block->child_node;
	if (iter->type != CMD)
		iter = iter->next_sib_node;
	if (!iter)
		return (NULL);
	iter = iter->child_node;
	return (iter);
}

int	exec_and_exit(t_ast *cmd, char **envv[],
	int (*f)(t_ast *cmd, char **envv[]))
{
	int	exit_code;

	exit_code = f(cmd, envv);
	if (exit_code >= 0)
		return (exit_code);
	return (EXIT_FAILURE);
}

int	is_builtin(t_ast *exec_block)
{
	t_ast	*iter;

	iter = get_term(exec_block);
	if (!iter)
		return (0);
	if (!ft_strncmp(iter->value, "echo", 5))
		return (1);
	if (!ft_strncmp(iter->value, "cd", 3))
		return (1);
	if (!ft_strncmp(iter->value, "pwd", 4))
		return (1);
	if (!ft_strncmp(iter->value, "env", 4))
		return (1);
	if (!ft_strncmp(iter->value, "export", 7))
		return (1);
	if (!ft_strncmp(iter->value, "unset", 6))
		return (1);
	if (!ft_strncmp(iter->value, "exit", 5))
		return (1);
	return (0);
}

void	exec_builtin(t_ast *exec_block, char **envv[])
{
	t_ast	*iter;
	int		exit_code;

	iter = get_term(exec_block);
	if (!ft_strncmp(iter->value, "echo", 5))
		exit_code = exec_echo(iter, envv);
	if (!ft_strncmp(iter->value, "cd", 3))
		exit_code = exec_cd(iter, envv);
	if (!ft_strncmp(iter->value, "pwd", 4))
		exit_code = exec_pwd(iter, envv);
	if (!ft_strncmp(iter->value, "env", 4))
		exit_code = exec_env(iter, envv);
	if (!ft_strncmp(iter->value, "export", 7))
		exit_code = exec_and_exit(iter, envv, exec_export);
	if (!ft_strncmp(iter->value, "unset", 6))
		exit_code = exec_and_exit(iter, envv, exec_unset);
	if (!ft_strncmp(iter->value, "exit", 5))
		exit_code = exec_exit(iter);
	exit(exit_code);
}
