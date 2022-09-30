/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 14:29:19 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/30 13:27:48 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "builtins.h"
#include <stdio.h>

int	check_n(char *arg)
{	
	int	i;

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
	int		i;
	t_ast	*tmp_cmd;

	i = 0;
	tmp_cmd = cmd;
	while (tmp_cmd->next_sib_node)
	{
		if (!i && !ft_strncmp(tmp_cmd->value, "echo", 5))
		{
			tmp_cmd = tmp_cmd->next_sib_node;
			i++;
		}
		if (!check_n(tmp_cmd->value))
			break ;
		i++;
		if (tmp_cmd->next_sib_node)
			tmp_cmd = tmp_cmd->next_sib_node;
	}
	if (check_n(tmp_cmd->value))
		return (-1);
	return (i);
}

int	get_first_arg(t_ast **cmd)
{
	int	i;
	int	index;

	i = 0;
	index = get_index_arg(*cmd);
	if (index == -1)
		return (-1);
	while (i < index && (*cmd)->next_sib_node)
	{
		*cmd = (*cmd)->next_sib_node;
		i++;
	}
	if (index > 1)
		return (1);
	return (0);
}

void	echo(t_ast *cmd)
{
	int		flag;
	t_ast	*tmp_cmd;

	tmp_cmd = cmd;
	flag = get_first_arg(&tmp_cmd);
	if (flag == -1)
		return ;
	if (!ft_strncmp(cmd->value, "echo", 5) && !cmd->next_sib_node)
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

int	exec_echo(t_ast *cmd, char **envv[])
{
	echo(cmd);
	update_underscore(cmd, envv);
	return (0);
}
