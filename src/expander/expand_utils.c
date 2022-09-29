/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:50:50 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/29 11:43:06 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "builtins.h"

int	get_exp_len(t_env_var *env_var_list, int len_input)
{
	int	exp_len;

	exp_len = 0;
	while (env_var_list)
	{
		exp_len += env_var_list->len_exp - env_var_list->len_env;
		env_var_list = env_var_list->next;
	}
	return (len_input + exp_len + 1);
}

char	*expand_input(char *input, t_env_var *env_list, int len)
{
	int		i;
	int		j;
	char	*exp;

	i = 0;
	j = 0;
	exp = ft_xmalloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		if (input[j] == '$')
		{
			ft_strlcpy(&exp[i], env_list->exp_env, (env_list->len_exp + 1));
			i += env_list->len_exp;
			j += env_list->len_env;
			env_list = env_list->next;
		}
		if (input[j] != '$')
		{
			exp[i] = input[j];
			i++;
			j++;
		}
	}
	exp[i] = '\0';
	return (exp);
}
