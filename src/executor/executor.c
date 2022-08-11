/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/11 15:21:57 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "executor.h"

#include <stdio.h>
static void	choose_pipe(int *pip1, int *pip2, int i)
{
	int	pipe_status;

	pipe_status = 0;
	if (i % 2 == 0)
	{
		pipe_status = pipe(pip1);
	}
	else
		pipe_status = pipe(pip2);
	if (pipe_status == -1)
		exit(EXIT_FAILURE);
}

static inline t_ast	*next_block(t_ast *exec_block)
{
	exec_block = exec_block->next_sib_node;
	if (exec_block && exec_block->type == TERMINAL)
		exec_block = exec_block->next_sib_node;
	return (exec_block);
}

static inline void	close_pipes(t_exec *data, int i)
{
	if (i % 2 == 0)
	{
		close(data->pip1[0]);
		close(data->pip1[1]);
	}
	else
	{
		close(data->pip2[0]);
		close(data->pip2[1]);
	}
}

static void	wait_loop(int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		wait(0);
		i++;
	}
}

int	executor(t_ast *ast, t_uint cmd_count, char *envp[])
{
	t_exec	data;
	t_ast	*exec_block;
	t_uint	i;
	int		status;

	i = 0;
	status = 0;
	exec_block = ast->child_node;
	data.cmd_count = cmd_count;
	while (i < cmd_count && exec_block)
	{
		if (i < cmd_count - 1 && cmd_count > 1)
			choose_pipe(data.pip1, data.pip2, i);
		data.pid = fork();
		if (data.pid == -1)
			exit(EXIT_FAILURE);
		else if (data.pid == 0)
		{
			extract_ast_data(exec_block, &data);
			execute_block(&data, envp, i);
		}
		exec_block = next_block(exec_block);
		i++;
	}
	close_pipes(&data, i);
	wait_loop(data.cmd_count);
	waitpid(data.pid, &status, 0);
	return (WEXITSTATUS(status));
}
