/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_redirects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:27:38 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/15 15:15:36 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "executor.h"

/*
	first command to be executed
*/
#include <stdio.h>

static inline void	first_cmd(t_exec *data)
{
	if (data->fd_in != 0)
		dup2(data->fd_in, STDIN_FILENO);
	if (data->cmd_count > 1 && data->fd_out == 0)
		dup2(data->pip1[1], STDOUT_FILENO);
	else if (data->fd_out != 0)
		dup2(data->fd_out, STDOUT_FILENO);
}

/*
	last command to be executed
*/
static inline void	last_cmd(t_exec *data)
{
	if (data->cmd_count % 2 == 0)
	{
		dup2(data->pip1[0], STDIN_FILENO);
	}
	else
	{
		dup2(data->pip2[0], STDIN_FILENO);
	}
	if (data->fd_in != 0)
		dup2(data->fd_in, STDIN_FILENO);
}

/*
	commands executed between the first and last commands
*/
static inline void	mid_cmd(t_exec *data, t_uint i)
{
	if (data->fd_in != 0)
		dup2(data->fd_in, STDIN_FILENO);
	if (i % 2 != 1)
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

void	handle_redirects(t_exec *data, t_uint i)
{
	if (i == 1)
		first_cmd(data);
	else if (i == data->cmd_count)
		last_cmd(data);
	else
		mid_cmd(data, i);
}