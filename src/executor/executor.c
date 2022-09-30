/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/30 13:31:22 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "executor.h"
#include "builtins.h"
#include "error_handling.h"

static int	count_cmds(t_ast *tree)
{
	t_ast	*iter;
	int		i;

	i = 0;
	iter = tree->child_node;
	while (iter)
	{
		if (iter->type == EXEC_BLOCK)
			i++;
		iter = iter->next_sib_node;
	}
	return (i);
}

static inline t_ast	*next_block(t_ast *exec_block)
{
	exec_block = exec_block->next_sib_node;
	if (exec_block)
		exec_block = exec_block->next_sib_node;
	return (exec_block);
}

static inline void	execute(t_ast *exec_block, t_exec *data, char *envv[])
{
	if (data->cmd)
	{
		if (is_builtin(exec_block))
			exec_builtin(exec_block, &envv);
		if (access(data->cmd[0], F_OK | X_OK) != 0)
		{
			cmd_error_exit(data->cmd[0]);
		}
		execve(data->cmd[0], data->cmd, envv);
		cmd_error_exit(data->cmd[0]);
	}
	exit(EXIT_SUCCESS);
}

void	executor_loop(t_ast *exec_block, t_exec *data, char *envv[])
{
	t_uint	i;

	i = 0;
	while (i < data->cmd_count && exec_block)
	{
		choose_pipe(data, i);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			extract_ast_data(exec_block, data, envv);
			handle_redirects(data, i);
			execute(exec_block, data, envv);
		}
		close_pipe(data, i);
		exec_block = next_block(exec_block);
		i++;
	}
}

int	executor(t_ast *tree, char **envv[])
{
	t_exec	data;
	t_ast	*first_cmd;
	int		status;
	t_uint	i;

	i = 0;
	status = 0;
	first_cmd = tree->child_node;
	data.cmd_count = count_cmds(tree);
	init_pipes(data.pip1, data.pip2);
	if (data.cmd_count == 1 && is_builtin(first_cmd))
		return (exec_single_builtin(first_cmd, envv));
	data.pid = ft_xmalloc(data.cmd_count * sizeof(int));
	executor_loop(first_cmd, &data, *envv);
	waitpid(data.pid[data.cmd_count - 1], &status, 0);
	while (i < data.cmd_count - 1)
	{
		wait(0);
		i++;
	}
	free(data.pid);
	return (get_exitcode(status));
}
