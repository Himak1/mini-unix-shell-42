/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getcmd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:32:53 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/26 15:39:14 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>

static t_uint	child_count(t_ast *node)
{
	t_ast	*iter;
	t_uint	i;

	i = 0;
	iter = node;
	while (iter)
	{
		iter = iter->next_sib_node;
		i++;
	}
	return (i);
}

char	**getcmd(t_ast *exec_block)
{
	char	**cmd;
	t_ast	*iter;
	t_uint	arg_count;
	t_uint	i;

	i = 0;
	cmd = NULL;
	iter = exec_block->child_node;
	if (iter->type != CMD)
		iter = iter->next_sib_node;
	if (!iter)
		return (NULL);
	iter = iter->child_node;
	arg_count = child_count(iter);
	cmd = ft_xmalloc((arg_count + 1) * sizeof(char *));
	cmd[arg_count] = NULL;
	while (iter)
	{
		cmd[i] = ft_strdup(iter->value);
		if (!cmd[i])
			exit(EXIT_FAILURE);
		iter = iter->next_sib_node;
		i++;
	}
	return (cmd);
}
