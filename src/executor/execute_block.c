/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_block.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 14:19:58 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/11 14:21:20 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "executor.h"

#include <stdio.h>

/*
	first command to be executed
*/
static inline void	first_cmd(t_exec *data)
{
	if (data->cmd_count > 1)
	{
		dup2(data->pip1[1], STDOUT_FILENO);
	}
	close(data->pip1[0]);
	close(data->pip1[1]);
}

/*
	last command to be executed
*/
static inline void	last_cmd(t_exec *data, t_uint i)
{
	if (i % 2 == 1)
	{
		dup2(data->pip1[0], STDIN_FILENO);
	}
	else
		dup2(data->pip2[0], STDIN_FILENO);
	close(data->pip1[1]);
	close(data->pip1[0]);
}

/*
	commands executed between the first and last commands
*/
static inline void	mid_cmd(t_exec *data, t_uint i)
{
	if (i % 2 == 1)
	{
		dup2(data->pip1[0], STDIN_FILENO);
		dup2(data->pip2[1], STDOUT_FILENO);
	}
	else
	{
		dup2(data->pip2[0], STDIN_FILENO);
		dup2(data->pip1[1], STDOUT_FILENO);
	}
}

void	execute_block(t_exec *data, char *envp[], t_uint i)
{
	if (i == 0)
		first_cmd(data);
	else if (i == data->cmd_count - 1)
		last_cmd(data, i);
	else
		mid_cmd(data, i);
	if (access(data->cmd[0], X_OK) != 0)
		exit(EXIT_FAILURE);
	execve(data->cmd[0], data->cmd, envp);
}
