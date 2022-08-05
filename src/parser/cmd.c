/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:59:01 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/05 11:56:17 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_cmd(t_token **list)
{
	t_ast	*output;

	if (*list && peek_tkn(*list) == WORD)
	{
		output = new_node(CMD);
		while (*list && peek_tkn(*list) == WORD)
			add_child(output, new_term_node(list));
	}
	else
		output = NULL;
	return (output);
}
