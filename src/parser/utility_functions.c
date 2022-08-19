/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 17:29:11 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/19 14:29:09 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_uint	peek_tkn(t_token *token)
{
	return (token->type);
}

t_uint	next_2_tkn(t_token *token, t_uint type1, t_uint type2)
{
	int	state;

	state = 0;
	if (peek_tkn(token) == type1)
	{
		if (token->next && peek_tkn(token->next) == type2)
			state = 1;
	}
	return (state);
}

/*
	Tries to find the RDS node. 
	If RDS is found it returns the RDS child node.
	Else it returns NULL
*/
t_ast	*get_rd(t_ast *exec_block)
{
	if (exec_block->child_node->type == RDS)
		return (exec_block->child_node->child_node);
	else if (exec_block->child_node->next_sib_node)
		return (exec_block->child_node->next_sib_node->child_node);
	else
		return (NULL);
}
