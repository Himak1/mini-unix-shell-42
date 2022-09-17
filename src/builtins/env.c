/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:09:10 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/17 18:24:23 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"
#include "builtins.h"
#include <stdio.h>

int env(char *envv[])
{
    int i;
    i = 0;
    while (envv[i])
    {
        if (ft_strchr(envv[i], '='))
            ft_putendl_fd(envv[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}

int exec_env(t_ast *cmd, char **envv[])
{
    update_underscore(cmd, envv);
    env(*envv);
    return (0);
}