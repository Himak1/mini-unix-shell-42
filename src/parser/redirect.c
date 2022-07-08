/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/08 15:18:29 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/08 17:30:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*rd_in(t_token **list, int *status)
{

}

t_ast	*rds(t_token **list, int *status)
{
	t_ast	*output;

	if (next_2_tkn(*list, RDR_IN, WORD)
		|| next_2_tkn(*list, WORD, RDR_OUT))
		output = new_node(RDS);
	if (output)
	{
		
	}
	return (output);
}

/*
t_ast	*rd_in(t_token **list, int *status)
{
	t_ast	*output;

	if (!next_2_tkn(*list, RDR_IN, WORD))
		return (NULL);
	output = new_node(RD_IN);
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
*/
