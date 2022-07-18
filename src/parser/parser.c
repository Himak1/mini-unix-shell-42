/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/18 16:34:18 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static inline int	is_rdr(t_token *list)
{
	return (peek_tkn(list) == RDR_IN || peek_tkn(list) == RDR_OUT
		|| peek_tkn(list) == RDR_DLM_IN || peek_tkn(list) == RDR_APND_OUT);
}

t_ast	*exec_block(t_token **list)
{
	t_ast	*output;
	int		cmd_parsed;

	cmd_parsed = 0;
	output = new_node(EXEC_BLOCK);
	while (*list)
	{
		if (is_rdr(*list) && rds(output, list) == -1)
		{
			free_child_nodes(output);
			free(output);
			return (NULL);
		}
		else if (*list && !cmd_parsed && peek_tkn(*list) == WORD)
			add_child(output, parse_cmd(list));
		else if (*list && cmd_parsed && peek_tkn(*list) == WORD)
		{
			// need to free child_nodes
			return (NULL);
		}
	}
	return (output);
}

t_ast	*pipe(t_token **list)
{
	if ()
}

t_ast	*parse_tokens(t_token **list)
{
	t_ast	*tree;

	tree = new_node(EXEC_CHAIN);
	if (add_child(tree, exec_block(list)) == -1)
	{
		free(tree);
		return (NULL);
	}
	while (*list)
	{
		if (pipe)
	}
	return (tree);
}
