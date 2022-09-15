/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 14:29:19 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/14 16:17:41 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "lexer.h"
#include "expander.h"
#include "executor.h"
#include "builtins.h"
#include <stdio.h>

// -n option is used to omit echoing trailing newline
//		eg. input
//		["echo", "hello", NULL];					->		hello\n
//		["echo", "-n", "hi", "hello", NULL]			->		hi hello
//		["echo", "-n", "-n", "hello", NULL]			->		hello
//		["echo", "-n", "-d", "hello", NULL]			->		-d hello
//		["echo", "-nnnnnnnn", "-n", "hello", NULL]	->		hello

int	check_n(char *arg)
{	
	int i;

	i = 0;
	while (arg[i] && arg[i] == '-')
	{
		if (arg[i] == '-')
			i++;
		while (arg[i] != '\0')
		{
			if (!i)
				i++;
			if (arg[i] == ' ' && i > 1)
				break ;
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		if (arg[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int	get_index_arg(t_ast *cmd)
{
	int i;
	t_ast *tmp_cmd;

	i = 0;
	tmp_cmd = cmd;
	while (tmp_cmd->next_sib_node)
	{
		if (!i && !ft_strncmp(tmp_cmd->value, "echo", ft_strlen(tmp_cmd->value)))
		{
			tmp_cmd = tmp_cmd->next_sib_node;
			i++;
		}
		if (!check_n(tmp_cmd->value))
			break ;
		i++;
		tmp_cmd = tmp_cmd->next_sib_node;
	}
	return (i);
}

int	get_first_arg(t_ast **cmd)
{
	int i;
	int index;

	i = 0;
	index = get_index_arg(*cmd);
	while (i < index && (*cmd)->next_sib_node)
	{
		*cmd = (*cmd)->next_sib_node;
		i++;
	}
	if (index > 1)
		return (1);
	return (0);
}


void echo(t_ast *cmd)
{
	int flag;
	t_ast *tmp_cmd;
	
	tmp_cmd = cmd;
	flag = get_first_arg(&tmp_cmd);
	if (!ft_strncmp(cmd->value, "echo", ft_strlen(cmd->value)) && !cmd->next_sib_node)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		while (tmp_cmd->next_sib_node)
		{
			ft_putstr_fd(tmp_cmd->value, STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
			tmp_cmd = tmp_cmd->next_sib_node;
		}
		if (flag)
			ft_putstr_fd(tmp_cmd->value, STDOUT_FILENO);
		else
			ft_putendl_fd(tmp_cmd->value, STDOUT_FILENO);
	}
}

int	exec_echo(t_ast *cmd, char *envp[])
{
	echo(cmd);
	update_underscore(cmd, envp);
	return (0);
}
