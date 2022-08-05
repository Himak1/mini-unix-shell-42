/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 11:41:44 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/03 15:08:56 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "expander.h"

int		get_env_var_len(char *env_var)
{
	int i;

	i = 0;
	while (env_var[i] != ' ' && env_var[i] != '\0')
	{
		i++;
		if (env_var[i] == '$' || env_var[i] == '\"' || env_var[i] == '\'')
			break ;
	}
	return (i);
}

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
	ft_free_2d_array(env_var);
}

// delete
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