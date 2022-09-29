/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:18:49 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/29 11:42:36 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "builtins.h"
#include <limits.h>
#include <stdio.h>

char	*create_full_var(char *key, char *value)
{
	char	*full_var;
	char	*key_is_equal;

	key_is_equal = ft_strjoin(key, "=");
	full_var = ft_strjoin(key_is_equal, value);
	free(key_is_equal);
	return (full_var);
}

void	update_var(int index, char *key, char *val, char *envv[])
{
	if (envv[index])
		free(envv[index]);
	if (!val)
		envv[index] = ft_strdup(key);
	else
		envv[index] = create_full_var(key, val);
}

void	update_underscore(t_ast *cmd, char **envv[])
{
	int		index;
	int		size;
	t_ast	*iter;

	size = 0;
	while ((*envv)[size])
		size++;
	index = ft_get_index_key(*envv, "_=");
	if (index == -1)
	{
		push_var_to_env("_=", envv);
		index = size;
	}
	iter = cmd;
	while (iter->next_sib_node)
		iter = iter->next_sib_node;
	update_var(index, "_", iter->value, *envv);
}

void	update_pwd(char *envv[])
{
	int		index;
	char	*new_path;
	char	cwd[PATH_MAX];

	new_path = NULL;
	index = ft_get_index_key(envv, "PWD=");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		new_path = ft_strdup(cwd);
	else
		perror("cd:");
	if (envv[index])
		free(envv[index]);
	envv[index] = create_full_var("PWD", new_path);
	free(new_path);
}

void	update_old_pwd(char **envv[])
{
	int		index;
	int		size;
	int		pwd_index;
	char	**current_pwd;

	size = 0;
	while ((*envv)[size])
		size++;
	index = ft_get_index_key(*envv, "OLDPWD=");
	if (index == -1)
	{
		push_var_to_env("OLDPWD=", envv);
		index = size;
	}
	pwd_index = ft_get_index_key(*envv, "PWD");
	current_pwd = ft_split((*envv)[pwd_index], '=');
	update_var(index, "OLDPWD", current_pwd[1], *envv);
	ft_free_2d_array(current_pwd);
}

// void	update_old_pwd(char **envv[])
// {
// 	int		index;
// 	int		size;
// 	int		pwd_index;
// 	char	**temp;
// 	char	**current_pwd;

// 	index = 0;
// 	temp = *envv;
// 	size = 0;
// 	while (temp[size])
// 		size++;
// 	while (temp[index])
// 	{
// 		if (ft_strnstr(temp[index], "OLDPWD", ft_strlen("OLDPWD")))
// 			break ;
// 		index++;
// 	}
// 	if (index == size)
// 	{
// 		push_var_to_env("OLDPWD=", envv);
// 		index = size;
// 	}
// 	temp = *envv;
// 	pwd_index = ft_get_index_key(*envv, "PWD");
// 	current_pwd = ft_split(temp[pwd_index], '=');
// 	update_var(index, "OLDPWD", current_pwd[1], *envv);
// 	ft_free_2d_array(current_pwd);
// }
