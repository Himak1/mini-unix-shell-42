/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/07 16:54:58 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*file(t_token **list, int *status)
{
	t_ast	*output;

	output = malloc(sizeof(t_ast));
	if (!output)
		return (set_error(status));
	output->value = ft_strdup((*list)->value);
	if (!output->value)
	{
		free(output);
		return (set_error(status));
	}
	*list = (*list)->next;
	return (output);
}

t_ast	*operate(t_token **list, const char *op_type, int *status)
{
	t_ast	*output;

	output = NULL;
	if (!ft_strncmp((*list)->value, op_type, ft_strlen((*list)->value)))
	{
		output = new_node(RD_IN);
		if (!output)
			return (set_error(status));
		output->value = ft_strdup((*list)->value);
		if (!output->value)
		{
			free(output);
			return (set_error(status));
		}
		*list = (*list)->next;
	}
	return (output);
}

t_ast	*rd_in(t_token **list, int *status)
{
	t_ast	*output[3];
	int		i;

	i = 0;
	if (next_2_tkn_cmp(*list, RDR_IN, WORD))
	{
		while (i < 3)
		{
			output[i] = malloc(sizeof(t_ast));
			if (!output[i])
			{
				free_array(output, i + 1);
				*status = -1;
			}
			i++;
		}
		if (*status != -1)
		{

		}
	}
	return (output[0]);
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
