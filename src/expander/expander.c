/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 14:27:25 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/25 15:40:38 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdio.h>
/*
NOTES:
-	$_			-> prints previous variable (expanded)
*/

int	count_dollar_sign(char *value)
{
	int count;

	count = 0;
	while (*value)
	{
		if (*value == '$')
			count++;
		value++;
	}
	return (count);
}

int		get_env_var_len(char *env_var)
{
	int i;

	i = 0;
	while (env_var[i] != ' ' && env_var[i] != '$' && env_var[i] != '\0')
		i++;
	return (i);
}

char	**get_env_var(char **env_var, char *value, int count)
{
	int i;
	int len;

	i = 0;
	while (*value && i < count)
	{
		if (*value == '$')
		{
			value++;
			len = get_env_var_len(value);
			env_var[i] = (char *)malloc(sizeof(char) * (len + 1));
			if (!env_var[i])
				return (ft_free_2d_array(env_var));
			ft_strlcpy(env_var[i], value, (len + 1));
			i++;
		}
		value++;
	}
	return (env_var);
}

char	**expand_dollar_sign(char *value)//, char **envp)
{
	int		count;
	char	*expanded_str;
	char	**env_var_values;
	
	if (!value)
		return (NULL);
	count = count_dollar_sign(value);
	env_var_values = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_var_values)
		return (NULL);
	env_var_values = get_env_var(env_var_values, value, (count + 1));
	//return(expanded_str);
	return(env_var_values);
}

char	*remove_quotes(char *value, char quote)
{
	int i;
	int count;
	char *value_without_quotes;

	i = 0;
	count = 0;
	while (value[i] != '\0')
	{
		if (value[i] != quote)
			count++;
		i++;
	}
	value_without_quotes = (char *)malloc(sizeof(char) * (count + 1));
	if (!value_without_quotes)
		return (NULL);
	ft_strlcpy(value_without_quotes, &value[1], (count + 1));
	return (value_without_quotes);
}

char	**create_envp()
{
	char **envp = NULL;
		envp = (char **)malloc((12) * sizeof(char *));
	envp[0] = ft_strdup("CHARSET=UTF-8");
	envp[1] = ft_strdup("HOSTNAME=a4d647f5f42a");
	envp[2] = ft_strdup("PWD=/pwd/desktop/minishell");
	envp[3] = ft_strdup("HOME=/root");
	envp[4] = ft_strdup("LANG=C.UTF-8");
	envp[5] = ft_strdup("TERM=xterm");
	envp[6] = ft_strdup("SHLVL=2");
	envp[7] = ft_strdup("LC_COLLATE=C");
	envp[8] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	envp[9] = ft_strdup("OLDPWD=/pwd/desktop/minishell/build");
	envp[10] = ft_strdup("_=/usr/bin/env");
	envp[11] = NULL;
	
	return (envp);
}

// void	expander(t_ast **tree)
// {
	
// }