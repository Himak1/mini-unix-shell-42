/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_new.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:52:49 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/01 15:38:48 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

t_token	*lst_new(t_uint type, char *value)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (new_node)
	{
		new_node->type = type;
		new_node->value = value;
		new_node->next = NULL;
	}
	return (new_node);
}
