/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:59:01 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/13 14:20:23 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_argument(t_ast *first_child, t_token **list)
{
	t_ast	*iter;

	iter = first_child;
	while (*list && peek_tkn(*list) == WORD)
	{
		iter->next_sib_node = new_term_node(list);
		iter = iter->next_sib_node;
	}
	return (0);
}

t_ast	*parse_cmd(t_token **list)
{
	t_ast	*output;

	if (*list && peek_tkn(*list) == WORD)
	{
		output = new_node(CMD);
		add_child(output, new_term_node(list));
		add_argument(output->child_node, list);
	}
	else
		output = NULL;
	return (output);
}
