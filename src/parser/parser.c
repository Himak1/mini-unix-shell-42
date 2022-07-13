/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/13 17:29:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static inline int	is_rdr(const t_token *list)
{
	return (peek_tkn(list) == RDR_IN || peek_tkn(list) == RDR_OUT);
}

t_ast	*exec_block(t_token **list)
{
	t_ast	*output;

	output = new_node(EXEC_BLOCK);
	while (*list)
	{
		if (is_rdr(*list) && rds(output, list) == -1)
		{
			free_child_nodes(output);
			free(output);
			return (NULL);
		}
		else if (peek_tkn(*list) == WORD)
			add_child(output, parse_cmd(list));
	}
	return (output);
}

t_ast	*parse_tokens(t_token **list, int *status)
{
	t_token	*new_token;
	t_ast	*tree;

	*status = *status;
	new_token = *list;
	tree = new_node(EXEC_CHAIN);
	while (new_token)
	{
		new_token = new_token->next;
	}
	return (tree);
}
