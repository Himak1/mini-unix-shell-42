/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_dollar_sign.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 17:38:34 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/28 17:43:36 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	if_forest(char *value, int *dquote, int )
{
	if (*value == '\"')
		dquote++;
	if (*value == '\'' && !dquote)
		squote++;
	if (*value == '$' && !squote)
		count++;
	if (squote == 2)
		squote = 0;
	if (dquote == 2)
		dquote = 0;
	value++;
}

int	count_dollar_sign(char *value, int *exit_code)
{
	int	dquote;
	int	squote;
	int	count;

	count = 0;
	squote = 0;
	dquote = 0;
	while (*value)
	{
		if (*value == '\"')
			dquote++;
		if (*value == '\'' && !dquote)
			squote++;
		if (*value == '$' && !squote)
			count++;
		if (squote == 2)
			squote = 0;
		if (dquote == 2)
			dquote = 0;
		value++;
	}
	if (dquote == 1 || squote == 1)
	{
		ft_putendl_fd("Syntax error: unclosed quote", STDERR_FILENO);
		*exit_code = -1;
	}
	return (count);
}
