/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:58 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/20 15:33:18 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "expander.h"
#include "builtins.h"
#include <stdio.h>


void pop_var_from_env(char *str, char **arr[])
{
    int i;
    int j;
    int index;
    int size;
    char **temp;
    char **new_arr;

    index = 0;
    temp = *arr;
    size = 0;
    while (temp[size])
        size++;
    while (temp[index])
    {
        if (ft_strnstr(temp[index], str, ft_strlen(str)))
            break;
        index++;
    }
    if (index == size && ft_strncmp(temp[index], str, ft_strlen(str)))
        return ;
    new_arr = ft_xmalloc(sizeof(char *) * size);
    i = 0;
    j = 0;
    while (j < size && temp[i])
    {
        if (i == index)
            i++;
        if (temp[i])
        {
            new_arr[j] = ft_strdup(temp[i]);
            i++;
            j++;
        }
    }
    new_arr[j] = NULL;
    ft_free_2d_array(*arr);
    *arr = new_arr;
}

void	print_envp(char **envp) //delete
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void unset(char *str, char **arr[])
{
    int index;

    index = search_for_key(str, *arr);
    printf("index = %i\n", index);
    if (index != -1)
        pop_var_from_env(str, arr);
}

int exec_unset(t_ast *cmd, char **envv[])
{
	t_ast *tmp;

    if (cmd->next_sib_node)
    {
        tmp = cmd->next_sib_node;
        while (tmp->next_sib_node)
        {
            //printf("hello");
            unset(tmp->value, envv);
            tmp = tmp->next_sib_node;
        }
        unset(tmp->value, envv);
    }
	//update_envv(cmd, envv);
	return (0);
}