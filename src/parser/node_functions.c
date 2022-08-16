/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 14:11:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/16 12:20:42 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*new_node(int type)
{
	t_ast	*output;

	output = xmalloc(sizeof(t_ast));
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
	if (!child)
		return (-1);
	if (!parent->child_node)
		parent->child_node = child;
	else
	{
		tmp = parent->child_node;
		while (tmp->next_sib_node)
			tmp = tmp->next_sib_node;
		tmp->next_sib_node = child;
		child->prev_sib_node = tmp;
	}
	return (0);
}

// new_term_node() creates a new terminal node
t_ast	*new_term_node(t_token **list)
{
	t_ast	*output;

	output = new_node(TERMINAL);
	output->value = (*list)->value;
	*list = (*list)->next;
	return (output);
}

void	free_child_nodes(t_ast *parent)
{
	t_ast	*iter;

	if (!parent->child_node)
		return ;
	iter = parent->child_node;
	while (iter->next_sib_node)
		iter = iter->next_sib_node;
	while (iter->prev_sib_node)
	{
		free_child_nodes(iter);
		iter = iter->prev_sib_node;
		free(iter->next_sib_node);
	}
	free_child_nodes(iter);
	free(iter);
}

void	free_ast(t_ast *parent)
{
	t_ast	*iter;

	if (!parent->child_node)
		return ;
	iter = parent->child_node;
	while (iter->next_sib_node)
		iter = iter->next_sib_node;
	while (iter->prev_sib_node)
	{
		free_child_nodes(iter);
		iter = iter->prev_sib_node;
		if (iter->next_sib_node->type == TERMINAL)
			free(iter->next_sib_node->value);
		free(iter->next_sib_node);
	}
	free_child_nodes(iter);
	free(iter);
}
