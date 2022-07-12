/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/12 14:33:30 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_tokens(t_token **list, int *status)
{
	t_token	*new_token;
	t_ast	*tree;

	*status = *status;
	new_token = *list;
	tree = new_node(EXE_CHAIN);
	while (new_token)
	{
		new_token = new_token->next;
	}
	return (tree);
}
