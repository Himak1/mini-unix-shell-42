/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 17:29:11 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/12 14:13:23 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*set_error(int *status)
{
	*status = -1;
	return (NULL);
}

t_uint	peek_tkn(t_token *token)
{
	return (token->type);
}

t_uint	next_2_tkn(t_token *token, t_uint type1, t_uint type2)
{
	int	state;

	state = 0;
	if (peek_tkn(token) == type1)
	{
		if (token->next && peek_tkn(token->next) == type2)
			state = 1;
	}
	return (state);
}
