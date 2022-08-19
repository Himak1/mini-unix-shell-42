/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getfd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:31:04 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/18 13:58:58 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "executor.h"

static int	fd_out(char *filename)
{
	if (access(filename, R_OK | W_OK) == 0)
		unlink(filename);
	return (open(filename, O_CREAT | O_WRONLY, 0666));
}

static int	fd_in(char *filename)
{
	return (open(filename, O_RDONLY));
}

// int	getfd(t_ast *exec_block, t_uint rd_type)
// {
// 	t_ast	*iter;
// 	int		ret_fd;

// 	ret_fd = 0;
// 	iter = exec_block->child_node;
// 	if (iter->type != RDS)
// 		iter = iter->next_sib_node;
// 	if (!iter)
// 		return (0);
// 	iter = iter->child_node;
// 	while (iter)
// 	{
// 		if (iter->type == rd_type && rd_type == RD_IN)
// 			ret_fd = fd_in(rd->child_node->next_sib_node->value);
// 		else if (iter->type == rd_type && rd_type == RD_OUT)
// 			ret_fd = fd_out(rd->child_node->next_sib_node->value);
// 		else if (iter->type == rd_type && rd_type == RD_OUT)
			
// 		iter = iter->next_sib_node;
// 	}
// 	return (ret_fd);
// }

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

