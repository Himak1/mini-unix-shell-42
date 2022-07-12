/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/12 16:54:31 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*exec_block(t_token **list, int *status)
{
	t_ast	*output;
	t_ast	*rd;
	t_ast	*cmd;

	rd = rds(list, status);
	if (*status == -1)
		return (NULL);
	cmd = parse_cmd(list, status);
	if (*status == -1)
	{
		free_child_nodes()
		return ()
	}
}

t_ast	*parse_tokens(t_token **list, int *status)
{
	t_token	*new_token;
	t_ast	*tree;

	*status = *status;
	new_token = *list;
	tree = new_node(EXEC_CHAIN);
	while (new_token)
	{
		new_token = new_token->next;
	}
	return (tree);
}
