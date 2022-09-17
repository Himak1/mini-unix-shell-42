/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:18:49 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/17 19:08:18 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "expander.h"
#include "builtins.h"
#include <limits.h>
#include <stdio.h>

int ft_len_2d_arr(char **arr)
{
	int i;
	
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int    compare_key(char *full_var, char *key)
{
    size_t i;

    i = 0;
    while (full_var[i] && full_var[i] != '=')
        i++;
    if (i == ft_strlen(key))
      return (1);
    return (0);
}

char	*create_full_var(char *key, char *value)
{
	char	*key_is_equal;
	char	*full_var;

	key_is_equal = ft_strjoin(key, "=");
	full_var = ft_strjoin(key_is_equal, value);
	free(key_is_equal);
	return (full_var);
}

void update_var(int index, char *key, char *val, char *envv[])
{
	free(envv[index]);
	envv[index] = create_full_var(key, val);
}

void update_underscore(t_ast *cmd, char **envv[])
{
    int index;
    int size;
    char **temp;
    t_ast *iter;

    index = 0;
    temp = *envv;
    size = 0;
    while (temp[size])
        size++;
    while (temp[index])
    {
        if (ft_strnstr(temp[index], "_", ft_strlen("_")) && compare_key(temp[index], "_"))
		   break;
        index++;
    }
    if (index == size) //has not been found
    {
	    push_var_to_env("_=", envv);
		index = size;
	}
	iter = cmd;
	while (iter->next_sib_node)
		iter = iter->next_sib_node;
	update_var(index, "_", iter->value, *envv);
}

void update_pwd(char *envv[])
{
	int		index;
	char	*new_path;
	char cwd[PATH_MAX];
	
	new_path = NULL;
	index = ft_get_index_2d(envv, "PWD=");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		new_path = ft_strdup(cwd);
	else
		perror("cd:");
	if (envv[index])
		free(envv[index]); // error with this?
	envv[index]= create_full_var("PWD", new_path);
	free(new_path);
}

void update_old_pwd(char **envv[]) //clean up
{
	int index;
    int size;
    char **temp;

    index = 0;
    temp = *envv;
    size = 0;
    while (temp[size])
        size++;
    while (temp[index])
    {
        if (ft_strnstr(temp[index], "OLDPWD", ft_strlen("OLDPWD")) && compare_key(temp[index], "OLDPWD"))
		   break;
        index++;
    }
    if (index == size) //has not been found
    {
	    push_var_to_env("OLDPWD=", envv);
		index = size;
	}
	temp = *envv;
	int pwd_index = ft_get_index_2d(*envv, "PWD");
	char **current_pwd = ft_split(temp[pwd_index], '=');
	update_var(index, "OLDPWD", current_pwd[1], *envv);
	ft_free_2d_array(current_pwd);
}