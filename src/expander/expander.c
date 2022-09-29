/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 14:27:25 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/29 11:43:16 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"

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
		*exit_code = error_unclosed_quote();
	return (count);
}

void	free_env_var_list(t_env_var *list)
{
	t_env_var	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		free(list->env_value);
		free(list->exp_env);
		free(list);
		list = tmp;
	}
}

char	*expand_dollar_sign(char *input, char **envv, int *exit_code)
{
	int			len_input;
	int			len_exp;
	char		*exp_input;
	char		**env_var;
	t_env_var	*env_var_list;

	env_var_list = NULL;
	len_input = ft_strlen(input);
	env_var = get_env_var(input, exit_code);
	if (!env_var)
		return (ft_strdup(input));
	create_env_var_list(&env_var_list, env_var);
	check_env_var(&env_var_list, envv);
	len_exp = get_exp_len(env_var_list, len_input);
	exp_input = expand_input(input, env_var_list, len_exp);
	free_env_var_list(env_var_list);
	return (exp_input);
}

int	expander(char **input, char **envv)
{
	int		error;
	char	*expanded;

	error = 0;
	expanded = expand_dollar_sign(*input, envv, &error);
	if (error == -1)
		return (error);
	expanded = remove_quotes(expanded);
	if (expanded)
		free(*input);
	*input = expanded;
	return (0);
}

int	expand_tree(t_ast *parent, char **envv)
{
	int		error;
	t_ast	*iter;

	error = 0;
	if (!parent->child_node)
		return (0);
	iter = parent->child_node;
	while (iter->next_sib_node)
		iter = iter->next_sib_node;
	while (iter->prev_sib_node)
	{
		error += expand_tree(iter, envv);
		if (iter->type == TERMINAL)
			error += expander(&(iter->value), envv);
		iter = iter->prev_sib_node;
	}
	if (iter->type == TERMINAL)
		error += expander(&(iter->value), envv);
	error += expand_tree(iter, envv);
	return (error);
}
