/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:09:22 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/22 13:31:45 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//exit 2 miljoen %205 rest

#include "utils.h"
#include "parser.h"
#include <stdio.h>

// exit [N]     ->      terminates the current shell (or script).
// If N is given, the return code to the parent process is set to N. 
// If not, the returned status the the status of the most recently executed command (i.e. $?).
// exit status: 255, invalid (e.g. non-numeric) argument - this staus is returned to the parent

// exit (no args)
// -> prints "exit" on stderr
// -> sets exit_code to 0
// -> exits the shell

// static void ft_exit(int exit_code)
// {
//     ft_putendl_fd()
// }

// exit (with valid arg N)
// -> prints "exit" on stderr
// -> sets exit_code to N
// -> exits the shell 

// exit (with invalid arg N -> non numeric)
// -> prints "exit" on stderr
// -> prints error message "bash: exit: a: numeric argument required"
// -> sets exit_code to 255
// -> exits the shell

// exit (with invalid arg N -> too many args)
// -> prints "exit" on stderr
// -> prints error message "bash: exit: a: numeric argument required"
// -> sets exit_code to 1
// -> DOES NOT EXIT THE SHELL

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
    exit(n);
}

int exec_exit(t_ast *cmd)
{
    if (!cmd->next_sib_node)
    {
        ft_putendl_fd("exit", STDERR_FILENO);
        exit(EXIT_SUCCESS);
        
    }
    else
    {
        exit_with_args(cmd->next_sib_node);
        return (1);
    }
	return (0);
}

