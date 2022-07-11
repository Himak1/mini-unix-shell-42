/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/08 15:18:29 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/11 13:21:35 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*rd_in(t_token **list, int *status)
{
	t_ast	*output;

	output = new_node(RD_IN);
	if (!output)
		return (set_error(status));
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
	return (output);
}

t_ast	*rd_out(t_token **list, int *status)
{
	t_ast	*output;

	output = new_node(RD_OUT);
	if (!output)
		return (set_error(status));
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
	return (output);
}

t_ast	*rds(t_token **list, int *status)
{
	t_ast	*output;
	t_uint	io;

	io = 0;
	output = NULL;
	if (next_2_tkn(*list, RDR_IN, WORD))
		io = 1;
	else if (next_2_tkn(*list, WORD, RDR_OUT))
		io = 2;
	else
		return (NULL);
	output = new_node(RDS);
	if (!output)
		return (set_error(status));
	if (io == 1)
		output->child_node = rd_in(list, status);
	else
		output->child_node = rd_out(list, status);
	if (*status == -1)
	{
		free(output);
		output = NULL;
	}
	return (output);
}
