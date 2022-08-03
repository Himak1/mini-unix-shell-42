/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getfd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:31:04 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/03 15:16:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "executor.h"

int	getfd(t_ast *exec_block, int rd_type)
{
	t_ast	*iter;
	t_ast	*rd;
	int		fd_in;

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
	if (rd)
		return (open(rd->child_node->next_sib_node, O_RDONLY));
	return (0);
}
