/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_exp_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 17:08:51 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/29 09:26:57 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "builtins.h"

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

char	*find_exp_var(char *env_var, char **envv)
{
	int		index;
	char	*exp_var;
	char	*exit_code;

	if (!ft_strncmp(env_var, "$_", ft_strlen(env_var)))
		index = ft_get_index_key(envv, "_=");
	else
		index = ft_get_index_key(envv, &env_var[1]);
	exp_var = NULL;
	if (!ft_strncmp(env_var, "$", ft_strlen(env_var)))
		return (ft_strdup(env_var));
	if (!ft_strncmp(env_var, "$?", ft_strlen(env_var)))
	{
		exit_code = ft_itoa(g_exit_code);
		return (exit_code);
	}
	if (index >= 0)
	{
		exp_var = save_exp_val(envv[index], &env_var[1]);
		return (exp_var);
	}
	return (exp_var);
}

void	check_env_var(t_env_var **env_var_list, char **envv)
{
	t_env_var	*head;

	head = *env_var_list;
	while (*env_var_list)
	{
		(*env_var_list)->exp_env
			= find_exp_var((*env_var_list)->env_value, envv);
		if ((*env_var_list)->exp_env)
			(*env_var_list)->len_exp = ft_strlen((*env_var_list)->exp_env);
		*env_var_list = (*env_var_list)->next;
	}
	*env_var_list = head;
}
