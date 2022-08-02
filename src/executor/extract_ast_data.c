/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_ast_data.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 13:32:57 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/02 17:18:29 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "executor.h"

static inline int	open_file(t_ast *rd)
{
	return (open(rd->child_node->next_sib_node, O_RDONLY));
}

static int	getfd(t_ast *exec_block, int rd_type)
{
	t_ast	*iter;
	t_ast	*rd;
	int		fd_in;

	rd = NULL;
	iter = exec_block->child_node;
	if (iter->type != RDS)
		iter = next_sib_node;
	iter = iter->child_node;
	while (iter)
	{
		if (iter->type == rd_type)
			rd_in = iter;
		iter = iter->next_sib_node;
	}
	if (rd)
		return (open_file(rd));
	return (0);
}

static char	**getcmd(t_ast *exec_block)
{
	char	**cmd;
	t_ast	*iter;

	cmd = NULL;
	iter = exec_block->child_node;
	if (iter->type != CMD)
		iter = iter->next_sib_node;
	if (!iter)
		return (NULL);
	iter = iter->child_node;
	// get length of list
	while (iter)
	{

		iter = iter->next_sib_node;
	}
}

char	**extract_ast_data(t_ast *exec_block, t_exec *data)
{
	data->fd_in = getfd(exec_block, RD_IN);
	data->fd_out = getfd(exec_block, RD_OUT);
	if (data->fd_in == -1 || data->fd_out == -1)
		exit(EXIT_FAILURE);
	data->cmd = getcmd(exec_block);
}
