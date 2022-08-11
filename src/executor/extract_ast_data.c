/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_ast_data.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 13:32:57 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/11 15:20:48 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	extract_ast_data(t_ast *exec_block, t_exec *data)
{
	data->fd_in = getfd(exec_block, RD_IN);
	data->fd_out = getfd(exec_block, RD_OUT);
	if (data->fd_in == -1 || data->fd_out == -1)
		exit(EXIT_FAILURE);
	data->cmd = getcmd(exec_block);
	add_cmd_path(data->cmd);
	data->pip1[0] = 0;
	data->pip1[1] = 0;
	data->pip2[0] = 0;
	data->pip2[1] = 0;
}
