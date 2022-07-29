/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 14:27:25 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/29 16:52:05 by Tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "expander.h"
#include <stdio.h>

char	**get_env_var(char *input)
{
	int i;
	int len;
	int count;
	char **env_var;

	i = 0;
	count = count_dollar_sign(input);
	if (!count)
		return (NULL);
	env_var = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_var)
		return (NULL);
	while (*input && i < count)
	{
		if (*input == '$')
		{
			len = get_env_var_len(input);
			env_var[i] = (char *)malloc(sizeof(char) * (len + 1));
			if (!env_var[i])
				return (ft_free_2d_array(env_var));
			ft_strlcpy(env_var[i], input, (len + 1));
			i++;
		}
		input++;
	}
	env_var[i] = NULL;
	return (env_var);
}

t_env_var	*create_env_var(char *value)
{
	t_env_var	*new;

	new = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new)
		return (NULL);
	new->env_value = ft_strdup(value);
	new->len_env = ft_strlen(new->env_value);
	new->len_exp_env = 0;
	new->exp_env_value = NULL;
	new->next = NULL;
	return (new);
}

void	lst_add_bk_env_var(t_env_var **list, t_env_var *env_var)
{
	t_env_var	*iter;

	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = env_var;
}

void	create_env_var_list(t_env_var **env_var_list, char **env_var)
{
	int			i;
	t_env_var	*new;

	i = 0;
	while (env_var[i] != NULL)
	{
		new = create_env_var(env_var[i]);
		if (*env_var_list == NULL)
			*env_var_list = new;
		else
			lst_add_bk_env_var(env_var_list, new);
		i++;
	}
}

char	*save_exp_val(char *full_env_val, char *alias)
{
	int		len_alias;
	int		len_var;
	char	*val;

	len_alias = ft_strlen(alias);
	if (full_env_val[len_alias] != '=')
		return (NULL);
	len_var = ft_strlen(full_env_val) - len_alias;
	val = (char *)malloc(sizeof(char) * (len_var + 1));
	ft_strlcpy(val, &full_env_val[len_alias + 1], (len_var + 1));
	return (val);
}

char	*find_exp_var(char *env_var, char **envp)
{
	int i;
	char *exp_var;

	i = 0;
	if (!ft_strncmp(env_var, "$", ft_strlen(env_var)))
		return (ft_strdup(env_var));
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], &env_var[1], ft_strlen(env_var)) != NULL)
		{
			exp_var = save_exp_val(envp[i], &env_var[1]);
			return (exp_var);
		}
		i++;
	}
	return (NULL);
}

void	check_env_var(t_env_var **env_var_list, char **envp)
{
	t_env_var *head;
	head = *env_var_list;
	while (*env_var_list)
	{
		(*env_var_list)->exp_env_value = find_exp_var((*env_var_list)->env_value, envp);
		// printf("%s\n", (*env_var_list)->exp_env_value);
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
	return (len_input + exp_len);
}

// int main ()
// {
//     char **envp = create_envp();
//     char **env_var = get_env_var("hello $NAME");
//     int len_input = ft_strlen("hello $NAME");
//     t_env_var *env_var_list = NULL;
//     int exp_len;
    
//     create_env_var_list(&env_var_list, env_var);
//     check_env_var(&env_var_list, envp);
//     exp_len = get_exp_len(env_var_list, len_input);
    
// }



char	**expand_input(char *input, t_env_var *env_var_list, int len)
{
	char *expanded;

	expanded = (char *)malloc(sizeof(char) * (len + 1));
	if (!expanded)
		return (NULL);
	
	return (expanded);
}

// char	*expand_dollar_sign(char *input);//, char **envp)
// {
// 	int			len_input;
// 	int			len_exp;
// 	char		*exp_input;
// 	char		**env_var;
// 	char		**envp = create_envp(); //remove this
// 	t_env_var	*env_var_list;
	
// 	env_var_list = NULL;
// 	len_input = ft_strlen(input);
// 	env_var = get_env_var(input);
// 	if (!env_var)
// 		return (input);
// 	create_env_var_list(&env_var_list, env_var);
// 	check_env_var(&env_var_list, envp)
// 	len_exp = get_exp_len(env_var_list, len_input);
// 	exp_input = expand_input(input, env_var_list, len_exp);
// 	free(input)
// 	return (exp_input);
// }

















































// char	**expand_values()

// char	**expand_dollar_sign(char *value)//, char **envp)
// {
// 	int		count;
// 	char	*expanded_str;
// 	char	**env_var_values;
	
// 	if (!value)
// 		return (NULL);
// 	count = count_dollar_sign(value);
// 	env_var_values = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (!env_var_values)
// 		return (NULL);
// 	env_var_values = get_env_var(env_var_values, value, (count + 1));
// 	//return(expanded_str);
// 	return(env_var_values);
// }


// void	expander(t_ast **tree)
// {
	
// }