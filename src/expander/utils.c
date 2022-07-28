/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 11:41:44 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/26 14:54:40 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
	while (env_var[i] != ' ' && env_var[i] != '\0')
	{
		i++;
		if (env_var[i] == '$')
			break ;
	}
	return (i);
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
