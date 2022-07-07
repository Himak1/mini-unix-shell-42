/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/07 18:09:26 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// new_term_node() creates a new terminal node
t_ast	*new_term_node(t_token **list)
{
	t_ast	*output;

	output = malloc(sizeof(t_ast));
	if (output)
	{
		output->value = (*list)->value;
		output->type = TERMINAL;
	}
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

t_ast	*rd_in(t_token **list, int *status)
{
	t_ast	*output;

	if (!next_2_tkn(*list, RDR_IN, WORD))
		return (NULL);
	output = malloc(sizeof(t_ast));
	if (output)
	{
		if (add_child(output, new_term_node(list)) == -1)
		{
			free(output);
			return (set_error(status));
		}
		if (add_child(output, new_term_node(list)) == -1)
		{
			free_child_nodes(output);
			free(output);
			return (set_error(status));
		}
	}
	return (output);
}

/*
t_ast	*file()
t_ast	*base()
*/

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
