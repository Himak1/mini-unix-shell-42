/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:09:10 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/15 10:30:48 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"
#include "builtins.h"
#include <stdio.h>

int env(char *envp[])
{
    int i;
    
    i = 0;
    while (envp[i])
    {
        ft_putendl_fd(envp[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}

int exec_env(t_ast *cmd, char *envp[])
{
    env(envp);
    printf("test !! %s\n", cmd->value);
    //update_underscore(cmd, envp);
    return (0);
}