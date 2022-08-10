/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/10 17:41:11 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "executor.h"

static void	choose_pipe(int *pip1, int *pip2, int i)
{
	int	pipe_status;

	pipe_status = 0;
	if (i % 2 == 0)
		pipe_status = pipe(pip1);
	else
		pipe_status = pipe(pip2);
	if (pipe_status == -1)
		exit(EXIT_FAILURE);
}

void	init_pipes(t_exec *data)
{
	data->pip1[0] = 0;
	data->pip1[1] = 0;
	data->pip2[0] = 0;
	data->pip2[1] = 0;
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
	init_pipes(&data);
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
		exec_block = exec_block->next_sib_node;
		i++;
		waitpid(data.pid, &status, 0);
	}
	waitpid(data.pid, &status, 0);
	return (WEXITSTATUS(status));
}
