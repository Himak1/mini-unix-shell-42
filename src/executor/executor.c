/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/02 14:34:58 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	execute_block(char **cmd, int fd_in, int fd_out)
{

}

static void	choose_pipe(int *pip1, int *pip2, int i)
{
	int	pipe_status;

	pipe_status = 0;
	if (i % 2 == 0)
		pipe_status = pipe(pip1);
	else
		pipe_status = pipe(pip2);
	if (pipe_status == -1)
		exit(exit_failure);
}

int	executor(t_ast *ast, t_uint cmd_count)
{
	t_exec	data;
	t_ast	*exec_block;
	int		i;

	i = 0;
	exec_block = ast->child_node;
	while (i < cmd_count)
	{
		if (i < cmd_count - 1)
			choose_pipe(data->pip1, data->pip2);
		data->pid = fork();
		if (data->pid == -1)
			exit(EXIT_FAILURE);
		else if (data->pid == 0)
		{
			extract_ast_data(exec_block, &data);
			execute_block(data);
		}
		exec_block = exec_block->next_sib_node;
	}
	// save the last process return code;
}
