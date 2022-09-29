/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_ast_data.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 13:32:57 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/29 14:12:57 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

void	extract_ast_data(t_ast *exec_block, t_exec *data, char *envv[])
{
	data->fd_in = getfd_in(exec_block);
	data->fd_out = getfd_out(exec_block);
	if (data->fd_in == -1 || data->fd_out == -1)
		exit(EXIT_FAILURE);
	data->cmd = getcmd(exec_block);
	if (!data->fd_in
		&& !data->fd_out
		&& !ft_strncmp(data->cmd[0], "", ft_strlen(data->cmd[0])))
	{
		exit(EXIT_SUCCESS);
	}
	if (data->cmd && !is_builtin(exec_block))
		add_cmd_path(data->cmd, envv);
}
