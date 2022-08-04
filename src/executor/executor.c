/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/04 17:50:04 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

#include <stdio.h>
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

int	executor(t_ast *ast, t_uint cmd_count, char *envp[])
{
	t_exec	data;
	t_ast	*exec_block;
	t_uint	i;
	int		status;

	printf("%d\n", cmd_count);
	i = 0;
	status = 0;
	exec_block = ast->child_node;
	data.cmd_count = cmd_count;
	while (i < cmd_count && exec_block)
	{
		if (i < cmd_count - 1)
			choose_pipe(data.pip1, data.pip2, i);
		data.pid = fork();
		if (data.pid == -1)
			exit(EXIT_FAILURE);
		else if (data.pid == 0)
		{
			extract_ast_data(exec_block, &data);
			execute_block(&data, envp, i);
		}
		i++;
		exec_block = exec_block->next_sib_node;
	}
	waitpid(data.pid, &status, 0);
	return (WIFEXITED(status));
}
