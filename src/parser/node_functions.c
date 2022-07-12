/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 14:11:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/12 14:13:16 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*new_node(int type)
{
	t_ast	*output;

	output = malloc(sizeof(t_ast));
	if (!output)
		return (NULL);
	output->type = type;
	output->num_children = 0;
	output->value = NULL;
	output->child_node = NULL;
	output->next_sib_node = NULL;
	output->prev_sib_node = NULL;
	return (output);
}

int	add_child(t_ast *parent, t_ast *child)
{
	t_ast	*tmp;

	tmp = NULL;
	if (!parent || !child)
		return (-1);
	if (!parent->child_node)
		parent->child_node = child;
	else
	{
		tmp = parent->child_node;
		while (tmp->next_sib_node)
			tmp = tmp->next_sib_node;
		tmp->next_sib_node = child;
	}
	return (0);
}

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
