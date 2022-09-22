/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:50 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/20 19:18:01 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"
#include "builtins.h"
#include <stdio.h>

void push_var_to_env(char *str, char **arr[])
{
	int i;
    char **temp;
	char **new_arr;

	i = 0;
    temp = *arr;
	while (temp[i] != NULL)
		i++;
	new_arr = ft_xmalloc(sizeof(char *) * (i + 2));
	i = 0;
	while (temp[i] != NULL)
	{
		new_arr[i] = ft_strdup(temp[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	i++;
	new_arr[i] = NULL;
    ft_free_2d_array(*arr);
    *arr = new_arr;
}

static char **sort_alpha(char *arr[], int size)
{
    int i;
    int j;
    char *temp;
    char **sorted;
    
    temp = NULL;
    sorted = cpy_2d(arr);
    i = 1;
    while (i < size)
    {
        j = 1;
        while (j < size)
        {
            if(ft_strncmp(sorted[j-1], sorted[j], ft_strlen(sorted[j-1]))>0)
            {
                temp = ft_strdup(sorted[j-1]);
                free(sorted[j-1]);
                sorted[j-1] = ft_strdup(sorted[j]);
                free(sorted[j]);
                sorted[j] = ft_strdup(temp);
                free(temp);
            }
            j++;
        }
        i++;
    }
    return (sorted);
}

void print_with_quotes(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
    {
        ft_putchar_fd(str[i], STDOUT_FILENO);
        i++;
    }
    if (!str[i])
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        return ;
    }
    ft_putchar_fd(str[i], STDOUT_FILENO);
    i++;
    ft_putchar_fd('"', STDOUT_FILENO);
    while (str[i] && str[i] != '=')
    {
        ft_putchar_fd(str[i], STDOUT_FILENO);
        i++;
    }
    ft_putchar_fd('"', STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
}

void print_export_list(char *envv[])
{
    int envv_size;
    char **sorted_envv;

    envv_size = 0;
    while (envv[envv_size])
        envv_size++;
    sorted_envv = sort_alpha(envv, envv_size);
    envv_size = 0;
    while(sorted_envv[envv_size])
    {
        if (ft_strncmp(sorted_envv[envv_size], "_=", ft_strlen("_=")))
        {
            ft_putstr_fd("declare -x ", STDOUT_FILENO);
            print_with_quotes(sorted_envv[envv_size]);
        }
        envv_size++;
    }
    ft_free_2d_array(sorted_envv);
}

int search_for_key(char *key, char **arr)
{
    int i;
    char **key_and_val;

    i = 0;
    if (ft_strchr(key, '='))
    {
        key_and_val = ft_split(key, '=');
        i = ft_get_index_key(arr, key_and_val[0]);
        if (!ft_strncmp(arr[i], key_and_val[0], ft_strlen(key_and_val[0])))
        {
            ft_free_2d_array(key_and_val);
            return (i);
        }
    }
    i = ft_get_index_key(arr, key);
    if (!ft_strncmp(arr[i], key, ft_strlen(key)))
            return (i);
    return (-1);
}

static void export(char *str, char **arr[])
{
    int index;

    index = search_for_key(str, *arr);
    if (index != -1)
    {
        if (!ft_strchr(str, '='))
            return ;
        update_var(index, str, NULL, *arr);
    }
    else
        push_var_to_env(str, arr);
}

int exec_export(t_ast *cmd, char **envv[])
{
	t_ast *tmp;

    if (!cmd->next_sib_node)
        print_export_list(*envv);
    else
    {
        tmp = cmd->next_sib_node;
        while (tmp->next_sib_node)
        {
            export(tmp->value, envv);
            tmp = tmp->next_sib_node;
        }
        export(tmp->value, envv);
    }
    update_underscore(cmd, envv);
	return (0);
}