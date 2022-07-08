/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/08 16:52:37 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// new_term_node() creates a new terminal node
t_ast	*new_term_node(t_token **list)
{
	t_ast	*output;

	output = new_node(TERMINAL);
	if (output)
		output->value = (*list)->value;
	*list = (*list)->next;
	return (output);
}

void	free_child_nodes(t_ast *parent)
{
	t_ast	*iter;
	t_ast	*tmp;

	iter = parent->child_node;
	while (iter)
	{
		tmp = iter;
		iter = iter->next_sib_node;
		free(tmp);
	}
	parent->child_node = NULL;
}

/*
t_ast	*parse_tokens(t_token **list)
{
	t_token	*new_token;
	t_ast	*tree;

	new_token = *list;
	tree = new_node(EXE_CHAIN);
	while (new_token)
	{
		new_token = new_token->next;
	}
	return (tree);
}
*/
