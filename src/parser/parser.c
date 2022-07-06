/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 14:38:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/06 17:36:56 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
t_ast	*file()
{

}
*/

t_ast	*operate(t_token *list, const char *op_type, int *status)
{
	t_ast	*output;

	output = NULL;
	if (!ft_strncmp(list->value, op_type, ft_strlen(list->value)))
	{
		output = new_node(RD_IN);
		if (!output)
			return (set_error(status));
		output->value = ft_strdup(list->value);
		if (!output->value)
		{
			free(output);
			return (set_error(status));
		}
	}
	return (output);
}

/*
t_ast	*in(t_token *list)
{

	if (!list)
		return (NULL);
	
}
*/

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
