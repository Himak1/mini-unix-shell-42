/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_single_builtin.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 13:51:43 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/29 14:45:23 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "builtins.h"
#include "executor.h"

#include <stdio.h>
static void	builtin_redirect(t_ast *exec_block)
{
	int	fd_in;
	int	fd_out;

	fd_in = getfd_in(exec_block);
	fd_out = getfd_out(exec_block);
	if (fd_in)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out)
		dup2(fd_out, STDOUT_FILENO);
}

static inline void	reset_close_fd(int stdin, int stdout)
{
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
}

int	exec_single_builtin(t_ast *exec_block, char **envv[])
{
	t_ast	*iter;
	int		og_stdin;
	int     og_stdout;
	int		exit_code;

	exit_code = 1;
	iter = get_term(exec_block);
	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	builtin_redirect(exec_block);
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
	reset_close_fd(og_stdin, og_stdout);
	return (exit_code);
}
