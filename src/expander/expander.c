/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 14:27:25 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/05 11:55:04 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"
#include <stdio.h>

int	count_dollar_sign(char *value)
{
	int	count;

	count = 0;
	while (*value)
	{
		if (*value == '$')
			count++;
		value++;
	}
	return (count);
}

char	*remove_quotes(char *value, char quote)
{
	int		i;
	int		count;
	char	*new_value;

	i = 0;
	count = 0;
	if (value[i] != quote)
	{
		new_value = ft_strdup(value);
		free(value);
		return (new_value);
	}
	while (value[i] != '\0')
	{
		if (value[i] != quote)
			count++;
		i++;
	}
	new_value = (char *)malloc(sizeof(char) * (count + 1));
	if (!new_value)
		return (NULL);
	ft_strlcpy(new_value, &value[1], (count + 1));
	return (new_value);
}

void	free_env_var_list(t_env_var *list)
{
	t_env_var	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		free(list->env_value);
		free(list->exp_env_value);
		free(list);
		list = tmp;
	}
}

char	*expand_dollar_sign(char *input, char **envp)
{
	int			len_input;
	int			len_exp;
	char		*exp_input;
	char		**env_var;
	t_env_var	*env_var_list;

	env_var_list = NULL;
	len_input = ft_strlen(input);
	env_var = get_env_var(input);
	if (!env_var)
		return (input);
	create_env_var_list(&env_var_list, env_var);
	check_env_var(&env_var_list, envp);
	len_exp = get_exp_len(env_var_list, len_input);
	exp_input = expand_input(input, env_var_list, len_exp);
	free_env_var_list(env_var_list);
	return (exp_input);
}

void	expander(char **input, char **envp)
{
	char	*expanded;

	expanded = NULL;
	if (**input == '\'')
	{
		expanded = remove_quotes(*input, '\'');
		free(*input);
		*input = ft_strdup(expanded);
		free(expanded);
	}
	else
	{
		expanded = expand_dollar_sign(*input, envp);
		if (!expanded)
			expanded = remove_quotes(*input, '\"');
		else
			expanded = remove_quotes(expanded, '\"');
		//free(*input);
		*input = ft_strdup(expanded);
		free(expanded);
	}
}

void	expand_tree(t_ast *parent, char **envp)
{
	t_ast	*iter;

	if (!parent->child_node)
		return ;
	iter = parent->child_node;
	while (iter->next_sib_node)
		iter = iter->next_sib_node;
	while (iter->prev_sib_node)
	{
		expand_tree(iter, envp);
		if (iter->type == TERMINAL)
			expander(&(iter->value), envp);
		iter = iter->prev_sib_node;
	}
	if (iter->type == TERMINAL)
		expander(&(iter->value), envp);
	expand_tree(iter, envp);
}
