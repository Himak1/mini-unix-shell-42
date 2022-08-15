/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_pipes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 12:29:30 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/15 12:31:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "executor.h"

void	close_pipe(t_exec *data, t_uint i)
{
	if (i % 2 == 0 || i == 1)
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

void	choose_pipe(t_exec *data, t_uint i)
{
	int	pipe_status;

	if (i != 1 && data->cmd_count > 1)
	{
		pipe_status = 0;
		if (i % 2 == 0)
			pipe_status = pipe(data->pip1);
		else
			pipe_status = pipe(data->pip2);
		if (pipe_status == -1)
			exit(EXIT_FAILURE);
	}
}
