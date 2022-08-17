/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:59:01 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/17 13:41:36 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_cmd(t_ast *parent, t_token **list)
{
	t_ast	*output;

	if (!parent->child_node)
	{
		parent->child_node = new_node(CMD);
		output = parent->child_node;
	}
	else if (parent->child_node->type != CMD
		&& !parent->child_node->next_sib_node)
	{
		add_child(parent, new_node(CMD));
		output = parent->child_node->next_sib_node;
	}
	else if (parent->child_node->next_sib_node
		&& parent->child_node->next_sib_node->type == CMD)
		output = parent->child_node->next_sib_node;
	else
		output = parent->child_node;
	add_child(output, new_term_node(list));
	return (0);
}
