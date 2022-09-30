/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getfd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:31:04 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/30 14:58:19 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "executor.h"

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
			{
				unlink(iter->child_node->next_sib_node->value);
				ret_fd = open(iter->child_node->next_sib_node->value, \
					O_CREAT | O_WRONLY, 0666);
			}
			else
				ret_fd = open(iter->child_node->next_sib_node->value, \
					O_CREAT | O_APPEND | O_WRONLY, 0666);
		}
		iter = iter->next_sib_node;
	}
	return (ret_fd);
}
