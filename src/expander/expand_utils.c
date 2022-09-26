/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:50:50 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/23 20:16:06 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "builtins.h"
#include <stdio.h>

extern int	g_exit_code;

char	*save_exp_val(char *full_env_val, char *alias)
{
	int		len_alias;
	int		len_var;
	char	*val;

	len_alias = ft_strlen(alias);
	if (full_env_val[len_alias] != '=')
		return (NULL);
	len_var = ft_strlen(full_env_val) - len_alias;
	val = ft_xmalloc(sizeof(char) * (len_var + 1));
	ft_strlcpy(val, &full_env_val[len_alias + 1], (len_var + 1));
	return (val);
}

char	*find_exp_var(char *env_var, char **envp)
{
	int i;
	char *exp_var;
	char *exit_code;

	i = 0;
	exp_var = NULL;
	if (!ft_strncmp(env_var, "$", ft_strlen(env_var)))
		return (ft_strdup(env_var));
	if (!ft_strncmp(env_var, "$?", ft_strlen(env_var)))
	{
		exit_code = ft_itoa(g_exit_code);
		return (exit_code);
	}
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], &env_var[1], ft_strlen(envp[i])) != NULL)
		{
			exp_var = save_exp_val(envp[i], &env_var[1]);
			return (exp_var);
		}
		i++;
	}
	return (exp_var);
}

void	check_env_var(t_env_var **env_var_list, char **envp)
{
	t_env_var *head;
	head = *env_var_list;
	while (*env_var_list)
	{
		(*env_var_list)->exp_env_value = find_exp_var((*env_var_list)->env_value, envp);
		if ((*env_var_list)->exp_env_value)
			(*env_var_list)->len_exp_env = ft_strlen((*env_var_list)->exp_env_value);
		*env_var_list = (*env_var_list)->next;
	}
	*env_var_list = head;
}

int	get_exp_len(t_env_var *env_var_list, int len_input)
{
	int exp_len;

	exp_len = 0;
	while (env_var_list)
	{
		exp_len += env_var_list->len_exp_env - env_var_list->len_env;
		env_var_list = env_var_list->next;
	}
	return (len_input + exp_len + 1);
}


char	*expand_input(char *input, t_env_var *env_var_list, int len)
{
	int i;
	int j;
	char *expanded;

	expanded = (char *)malloc(sizeof(char) * (len + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (input[j] == '$')
		{
			ft_strlcpy(&expanded[i], env_var_list->exp_env_value, (env_var_list->len_exp_env + 1));
			i += env_var_list->len_exp_env;
			j += env_var_list->len_env;
			env_var_list = env_var_list->next;
		}
		if (input[j] != '$')
		{
			expanded[i] = input[j];
			i++;
			j++;	
		}
	}
	expanded[i] = '\0';
	return (expanded);
}
