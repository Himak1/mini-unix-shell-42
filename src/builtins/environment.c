/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:18:49 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/19 19:11:18 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "expander.h"
#include "builtins.h"

// if env is called _=/usr/bin/env
// anything else, expand to last arg of last used command (last terminal in ast)

void update_underscore(t_ast *cmd, char *envp[])
{
	int		index;
    t_ast	*iter;
	char	*last_arg;

    iter = cmd;
	index = ft_get_index_2d(envp, "_=");
	last_arg = NULL;
	free(envp[index]);
	if (!ft_strncmp(iter->value, "env", ft_strlen(iter->value)))
		envp[index] = ft_strdup("_=/usr/bin/env");
	else
	{
		while (iter->next_sib_node != NULL)
			iter = iter->next_sib_node;
		last_arg = ft_strdup(iter->value);
		envp[index]= ft_strjoin("_=", last_arg);
		free(last_arg);
	}
}

void update_pwd(char *path, char *envp[])
{
	int		index;
	char	*new_path;

	index = ft_get_index_2d(envp, "PWD=");
	new_path = ft_strdup(path);
	free(envp[index]);
	envp[index]= ft_strjoin("PWD=", new_path);
	free(new_path);
}

char	**set_var(char *name, char *envp[])
{
	int i;
	int index;
	int old_pwd;
	char **updated_envp;
	
	i = 0;
	index = 0;
	old_pwd = 1;
	while (envp[i] != NULL)
		i++;
	updated_envp = (char **)malloc(sizeof(char *) * i + 2);
	if (!ft_strncmp(name, "OLDPWD=", ft_strlen(name)))
	{
		i = ft_get_index_2d(envp, "ZDOTDIR=") + 1;
		old_pwd = 0;
	}
	while (envp[index] != NULL)
	{
		if (index == i && !old_pwd)
		{
			updated_envp[index] = ft_strdup("OLDPWD=");
			index++;
		}
		updated_envp[index] = ft_strdup(envp[index]);
		index++;
	}
	updated_envp[index] = NULL;
	ft_free_2d_array(envp);
	return (updated_envp);
}

void	print_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

void update_old_pwd(char *envp[])
{
	int index_old_pwd;
	int index_pwd;
	char *old_path;

	index_old_pwd = ft_get_index_2d(envp, "OLDPWD=");
	if (!index_old_pwd && !ft_strnstr(envp[index_old_pwd], "OLDPWD=", ft_strlen(envp[index_old_pwd])))
		envp = set_var("OLDPWD=", envp);
	print_envp(envp);
	index_pwd = ft_get_index_2d(envp, "PWD=");
	old_path = ft_strdup(envp[index_pwd]);
	if (index_old_pwd)
		free(envp[index_old_pwd]);
	envp[index_old_pwd] = ft_strjoin("OLDPWD=", old_path);
	free(old_path);
}