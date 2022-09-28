/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 17:14:59 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/28 17:28:27 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

static void	if_no_dollar_sign(int *i, int *j, char *expanded, char *input)
{
	if (input[*j] != '$')
	{
		expanded[*i] = input[*j];
		(*i) += 1;
		(*j) += 1;
	}
}

char	*expand_input(char *input, t_env_var *env_var_list, int len)
{
	int		i;
	int		j;
	char	*expanded;

	expanded = (char *)ft_xmalloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (input[j] == '$')
		{
			ft_strlcpy(&expanded[i], env_var_list->exp_env_value,
				(env_var_list->len_exp_env + 1));
			i += env_var_list->len_exp_env;
			j += env_var_list->len_env;
			env_var_list = env_var_list->next;
		}
		if_no_dollar_sign(&i, &j, expanded, input);
	}
	expanded[i] = '\0';
	return (expanded);
}
