/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_syntax_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 13:42:36 by jhille        #+#    #+#                 */
/*   Updated: 2022/10/03 13:52:35 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static int	find_operator_char(const char *token)
{
	t_uint	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '<'
			|| token[i] == '>'
			|| token[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	check_syntax_error(t_token **list)
{
	t_token	*iter;

	iter = *list;
	while (iter)
	{
		if (iter->type == WORD && find_operator_char(iter->value))
			return (1);
		iter = iter->next;
	}
	return (0);
}
