/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_block.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 14:19:58 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/05 13:08:46 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "executor.h"

#include <stdio.h>
static inline void	close_pipes(t_exec *data)
{
	if (data->pip1[0] == 0)
		return ;
	close(data->pip1[0]);
	close(data->pip1[1]);
	close(data->pip2[0]);
	close(data->pip2[1]);
}

void	execute_block(t_exec *data, char *envp[], t_uint i)
{
	if (i == 0) // first command to be executed
	{
		if (data->cmd_count > 1)
			dup2(data->pip1[0], STDOUT_FILENO);
	}
	else if (i == data->cmd_count - 1) // last command to be executed
	{
		if (i % 2 == 1)
			dup2(data->pip1[1], STDIN_FILENO);
		else
			dup2(data->pip2[1], STDIN_FILENO);
	}
	else
	{
		if (i % 2 == 1)
		{
			dup2(data->pip1[1], STDIN_FILENO);
			dup2(data->pip2[0], STDOUT_FILENO);
		}
		else
		{
			dup2(data->pip2[1], STDIN_FILENO);
			dup2(data->pip1[0], STDOUT_FILENO);
		}
	}
	close_pipes(data);
	execve(data->cmd[0], data->cmd, envp);
}
