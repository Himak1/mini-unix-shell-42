/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_ast_data.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 13:32:57 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/26 15:39:43 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>

void	extract_ast_data(t_ast *exec_block, t_exec *data, char *envv[])
{
	data->fd_in = getfd_in(exec_block);
	data->fd_out = getfd_out(exec_block);
	if (data->fd_in == -1 || data->fd_out == -1)
		exit(EXIT_FAILURE);
	data->cmd = getcmd(exec_block);
	if (data->cmd)
		add_cmd_path(data->cmd, envv);
}
