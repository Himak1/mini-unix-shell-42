/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/10/03 14:00:18 by jhille        ########   odam.nl         */
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
	free_ast(output);
	return (NULL);
}

t_ast	*exec_block(t_token **list)
{
	t_ast	*output;
	int		status;

	output = new_node(EXEC_BLOCK);
	while (*list)
	{
		if (is_rdr(*list))
			status = rds(output, list);
		else if (peek_tkn(*list) == WORD)
			status = parse_cmd(output, list);
		else if (peek_tkn(*list) == PIPE && !output->child_node)
			status = -1;
		else if (peek_tkn(*list) == PIPE)
			break ;
		if (status == -1)
			return (handle_syntax_error(output));
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

t_ast	*parse_tokens(t_token *list)
{
	t_ast	*tree;
	t_token	*lst_head;

	lst_head = list;
	if (!lst_head)
		return (NULL);
	tree = new_node(EXEC_CHAIN);
	if (add_child(tree, exec_block(&lst_head)) == -1)
	{
		free(tree);
		return (NULL);
	}
	while (lst_head)
	{
		if (add_child(tree, parse_pipe(&lst_head)) == -1)
			return (handle_syntax_error(tree));
		if (add_child(tree, exec_block(&lst_head)) == -1)
			return (handle_syntax_error(tree));
	}
	return (tree);
}
