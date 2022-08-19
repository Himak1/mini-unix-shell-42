/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getfd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:31:04 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/19 14:42:47 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "executor.h"

/*
static int	fd_out(t_ast *rd_node, int ret_fd)
{
	if (access(filename, R_OK | W_OK) == 0)
		unlink(filename);
	return (open(filename, O_CREAT | O_WRONLY, 0666));
}

static int	fd_in(t_ast *rd_node, int ret_fd)
{
	return (open(filename, O_RDONLY));
}
*/

int	getfd_in(t_ast *exec_block)
{
	t_ast	*iter;
	int		ret_fd;

	ret_fd = 0;
	iter = get_rd(exec_block);
	while (iter)
	{
		if (iter->type == RD_IN || iter->type == RD_DE)
		{
			if (ret_fd != 0)
				close(ret_fd);
			ret_fd = open(iter->next_sib_node->value, O_RDONLY);
			if (iter->type == RD_DE)
				unlink(iter->next_sib_node->value);
		}
	}
	return (ret_fd);
}

int	getfd_out(t_ast *exec_block)
{
	t_ast	*iter;
	int		ret_fd;

	ret_fd = 0;
	iter = get_rd(exec_block);
	while (iter)
	{
		if (iter->type == RD_OUT || iter->type == RD_AP)
		{
			if (ret_fd != 0)
				close(ret_fd);
			if (iter->type == RD_OUT)
				ret_fd = open(iter->next_sib_node->value, \
					O_CREAT | O_WRONLY, 0666);
			else
				open(iter->next_sib_node->value, \
					O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
	}
	return (ret_fd);
}

/*
int	getfd(t_ast *exec_block, t_uint rd_type)
{
	t_ast	*iter;
	t_ast	*rd;

	rd = NULL;
	iter = exec_block->child_node;
	if (iter->type != RDS)
		iter = iter->next_sib_node;
	if (!iter)
		return (0);
	iter = iter->child_node;
	while (iter)
	{
		if (iter->type == rd_type)
			rd = iter;
		iter = iter->next_sib_node;
	}
	if (rd && rd_type == RD_IN)
		return (fd_in(rd->child_node->next_sib_node->value));
	else if (rd && rd_type == RD_OUT)
		return (fd_out(rd->child_node->next_sib_node->value));
	return (0);
}
*/
