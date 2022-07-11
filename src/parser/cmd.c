/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:59:01 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/11 15:51:51 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_argument(t_ast *first_child, t_token **list, int *status)
{
	t_ast	*iter;

	iter = first_child;
	while (peek_tkn(*list) == WORD)
	{
		iter->next_sib_node = new_term_node(list);
		if (!iter->next_sib_node)
		{
			*status = -1;
			return (-1);
		}
		iter = iter->next_sib_node;
	}
	return (0);
}

t_ast	*cmd(t_token **list, int *status)
{
	t_ast	*output;

	output = NULL;
	if (*list && peek_tkn(*list) == WORD)
	{
		output = new_node(CMD);
		if (!output)
			return (set_error(status));
		if (add_child(output, new_term_node(list)) == -1)
		{
			free(output);
			return (set_error(status));
		}
		if (add_argument(output->child_node, list, status) == -1)
		{
			free_child_nodes(output);
			free(output);
			return (NULL);
		}
	}
	return (output);
}
