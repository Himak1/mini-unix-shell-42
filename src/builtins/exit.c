/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:09:22 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/22 14:43:36 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//exit 2 miljoen %205 rest

#include "utils.h"
#include "parser.h"
#include <stdio.h>

extern int	g_exit_code;

static int check_numeric(char *arg)
{
    int i;

    i = 0;
    
    while (arg[i] && arg[i] == ' ')
        i++;
    if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
        i++;
    while (arg[i] && ft_isdigit(arg[i]))
        i++;   
    if (arg[i])
        return (0);
    return (1);
}

static void handle_non_numeric(char *arg)
{
    ft_putendl_fd("exit", STDERR_FILENO);
    ft_putstr_fd("bash: exit: ", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putendl_fd(": numeric argument required", STDERR_FILENO);
    exit(255);
}

static void handle_too_many_args(void)
{
    ft_putendl_fd("exit", STDERR_FILENO);
    ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
}

int exit_with_args(t_ast *arg)
{
    int n;

    if (!check_numeric(arg->value))
        handle_non_numeric(arg->value);
    if (arg->next_sib_node)
    {
        handle_too_many_args();
        return (1);
    }
    ft_putendl_fd("exit", STDERR_FILENO);
    n = ft_atoi(arg->value);
    g_exit_code = n;
    exit(n);
}

int exec_exit(t_ast *cmd)
{
    if (!cmd->next_sib_node)
    {
        ft_putendl_fd("exit", STDERR_FILENO);
        g_exit_code = 0;
        exit(EXIT_SUCCESS);
        
    }
    else
    {
        exit_with_args(cmd->next_sib_node);
        return (1);
    }
	return (0);
}

