/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/13 15:55:06 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "executor.h"

#include <stdio.h>
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

static inline t_ast	*prev_block(t_ast *exec_block)
{
	exec_block = exec_block->prev_sib_node;
	if (exec_block && exec_block->type == TERMINAL)
		exec_block = exec_block->prev_sib_node;
	return (exec_block);
}

static inline void	execute(t_exec *data, char *envp[])
{
	if (data->pid != 0)
		wait(0);
	if (data->cmd)
	{
		if (access(data->cmd[0], X_OK) != 0)
			exit(EXIT_FAILURE);
		execve(data->cmd[0], data->cmd, envp);
	}
	exit(0);
}

void	executor_loop(t_ast *exec_block, t_exec *data, char *envp[])
{
	t_uint	i;

	i = data->cmd_count;
	init_pipes(data->pip1, data->pip2);
	while (i != 0 && exec_block)
	{
		choose_pipe(data, i);
		fprintf(stderr, "[%d][%d] || [%d][%d]\n", data->pip1[0], data->pip1[1],\
				data->pip2[0], data->pip2[1]);
		extract_ast_data(exec_block, data);
		handle_redirects(data, i);
		if (i != 1)
		{
			data->pid = fork();
			if (data->pid == -1)
				exit(EXIT_FAILURE);
			else if (data->pid != 0)
				break ;
		}
		else if (i == 1)
			break ;
		exec_block = prev_block(exec_block);
		i--;
	}
	close_pipe(data, i);
	execute(data, envp);
}

int	executor(t_ast *tree, char *envp[])
{
	t_exec	data;
	t_ast	*last_cmd;
	int		status;

	status = 0;
	data.cmd_count = count_cmds(tree);
	last_cmd = tree->child_node;
	while (last_cmd && last_cmd->next_sib_node)
		last_cmd = last_cmd->next_sib_node;
	data.pid = fork();
	if (data.pid == 0)
		executor_loop(last_cmd, &data, envp);
	waitpid(data.pid, &status, 0);
	return (WEXITSTATUS(status));
}
