/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/22 14:26:21 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static inline int	is_rdr(t_token *list)
{
	return (peek_tkn(list) == RDR_IN || peek_tkn(list) == RDR_OUT
		|| peek_tkn(list) == RDR_DLM_IN || peek_tkn(list) == RDR_APND_OUT);
}

static inline t_ast	*handle_syntax_error(t_ast *output)
{
	free_child_nodes(output);
	free(output);
	return (NULL);
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
			return (handle_syntax_error(output));
		else if (*list && !cmd_parsed && peek_tkn(*list) == WORD)
		{
			add_child(output, parse_cmd(list));
			cmd_parsed = 1;
		}
		else if (*list && cmd_parsed && peek_tkn(*list) == WORD)
			return (handle_syntax_error(output));
		else if (*list && !output->child_node && (peek_tkn(*list) == PIPE))
			return (handle_syntax_error(output));
		else if (*list && output->child_node && (peek_tkn(*list) == PIPE))
			break ;
	}
	return (output);
}

t_ast	*parse_pipe(t_token **list)
{
	t_ast	*output;

	output = NULL;
	if (*list && peek_tkn(*list) == PIPE)
	{
		output = new_term_node(list);
	}
	return (output);
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
		if (add_child(tree, parse_pipe(list)) == -1)
			return (handle_syntax_error(tree));
		if (add_child(tree, exec_block(list)) == -1)
			return (handle_syntax_error(tree));
	}
	return (tree);
}
