/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 17:29:11 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/05 17:20:18 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
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
