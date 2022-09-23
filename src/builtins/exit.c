/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:09:22 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/23 15:24:11 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"

extern int	g_exit_code;

static int	check_numeric(char *arg)
{
	int	i;

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

static void	handle_non_numeric(char *arg)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(255);
}

static int handle_too_many_args(void)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
	return (1);
}

int	exit_with_args(t_ast *arg)
{
	int	n;
	
	n = 0;
	if (!check_numeric(arg->value))
		handle_non_numeric(arg->value);
	else if (arg->next_sib_node)
		return (handle_too_many_args());
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		n = ft_atoi(arg->value);
		exit(n % 256);
	}
	return (n % 256);
}

int	exec_exit(t_ast *cmd)
{
	if (!cmd->next_sib_node)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	else
		return (exit_with_args(cmd->next_sib_node));
}
