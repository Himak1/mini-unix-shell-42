/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getfd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:31:04 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/21 17:35:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "executor.h"

#include <stdio.h>
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
			ret_fd = open(iter->child_node->next_sib_node->value, O_RDONLY);
			fprintf(stderr, "getfd_in: %s\n", iter->child_node->next_sib_node->value);
			if (iter->type == RD_DE)
				unlink(iter->child_node->next_sib_node->value);
		}
		iter = iter->next_sib_node;
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
				ret_fd = open(iter->child_node->next_sib_node->value, \
					O_CREAT | O_WRONLY, 0666);
			else
				open(iter->child_node->next_sib_node->value, \
					O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
		iter = iter->next_sib_node;
	}
	return (ret_fd);
}
