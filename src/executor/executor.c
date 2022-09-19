/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/19 15:00:17 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>
#include "executor.h"
#include "builtins.h"

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

static inline void	execute(t_exec *data, char *envv[])
{
	if (data->cmd)
	{
		if (access(data->cmd[0], X_OK) != 0)
			exit(EXIT_FAILURE);
		execve(data->cmd[0], data->cmd, envv);
		write(STDERR_FILENO, "Minishell: command not found\n", 29);
		exit(EXIT_FAILURE);
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
			extract_ast_data(exec_block, data);
			handle_redirects(data, i);
			execute(data, envv);
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
	data.pid = ft_xmalloc(data.cmd_count * sizeof(int));
	data.cmd_count = count_cmds(tree);
	init_pipes(data.pip1, data.pip2);
	if (!is_builtin(first_cmd, data.cmd_count))
	{
		executor_loop(first_cmd, &data, *envv);
		waitpid(data.pid[data.cmd_count - 1], &status, 0);
		while (i < data.cmd_count - 1)
		{
			wait(0);
			i++;
		}
	}
	else
		exec_builtin(first_cmd, *envv);
	return (WEXITSTATUS(status));
}
