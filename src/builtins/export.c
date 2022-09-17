/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:50 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/17 15:57:14 by tvan-der      ########   odam.nl         */
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
	new_arr = (char **)malloc(sizeof(char *) * (i + 2));
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
	//return (new_arr);
}

static void sort_alpha(char *arr[], int size)
{
    int i;
    int j;
    char *temp;
    
    temp = NULL;
    i = 1;
    while (i < size)
    {
        j = 1;
        while (j < size)
        {
            if(ft_strncmp(arr[j-1], arr[j], ft_strlen(arr[j-1]))>0)
            {
                temp = ft_strdup(arr[j-1]);
                free(arr[j-1]);
                arr[j-1] = ft_strdup(arr[j]);
                free(arr[j]);
                arr[j] = ft_strdup(temp);
                free(temp);
            }
            j++;
        }
        i++;
    }
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

    envv_size = 0;
    while (envv[envv_size])
        envv_size++;
    sort_alpha(envv, envv_size);
    //add_quotes(envv);
    envv_size = 0;
    while(envv[envv_size])
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        print_with_quotes(envv[envv_size]);
        envv_size++;
    }
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
            push_var_to_env(tmp->value, envv);
            tmp = tmp->next_sib_node;
        }
        push_var_to_env(tmp->value, envv);
    }
    //update_envv(cmd, envv);
	return (0);
}