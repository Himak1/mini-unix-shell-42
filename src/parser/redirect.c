/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/08 15:18:29 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/13 17:33:20 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*rd_in(t_token **list)
{
	t_ast	*output;

	output = new_node(RD_IN);
	add_child(output, new_term_node(list));
	add_child(output, new_term_node(list));
	return (output);
}

t_ast	*rd_out(t_token **list)
{
	t_ast	*output;

	output = new_node(RD_OUT);
	add_child(output, new_term_node(list));
	add_child(output, new_term_node(list));
	return (output);
}

t_ast	*rds(t_ast *parent, t_token **list)
{
	t_ast	*output;

	if (!parent->child_node)
		parent->child_node = new_node(RDS);
	else if (parent->child_node->type != RDS)
		add_child(parent, new_node(RDS));
	if (next_2_tkn(*list, RDR_IN, WORD))
		output = rd_in(list);
	else if (next_2_tkn(*list, WORD, RDR_OUT))
		output = rd_out(list);
	else
		return (NULL);
	return (output);
}
