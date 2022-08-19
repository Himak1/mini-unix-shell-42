/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 14:29:19 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/19 15:30:23 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "builtins.h"
#include <stdio.h>

// -n option is used to omit echoing trailing newline
//		eg. input
//		["echo", "hello", NULL];					->		hello\n
//		["echo", "-n", "hi", "hello", NULL]			->		hi hello
//		["echo", "-n", "-n", "hello", NULL]			->		hello
//		["echo", "-n", "-d", "hello", NULL]			->		-d hello
//		["echo", "-nnnnnnnn", "-n", "hello", NULL]	->		hello

//return index where
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

int	get_index_arg(char **arg)
{
	int i;

	i = 1;
	while (arg[i] != NULL)
	{
		if (!check_n(arg[i]))
			break ;
		i++;
	}
	return (i);
}

char	**extract_args(t_ast *cmd)
{
	int i;
	int len;
	t_ast *iter;
	char **args;

	i = 0;
	len = 0;
	iter = cmd;
	while (iter->next_sib_node != NULL)
	{
		iter = iter->next_sib_node;
		len++;
	}
	args = (char **)malloc(sizeof(char *) * (len + 1));
	iter = cmd;
	while (i < len + 1)// && iter->next_sib_node != NULL)
	{
		args[i] = ft_strdup(iter->value);
		i++;
		iter = iter->next_sib_node;
	}
	args[i] = NULL;
	return (args);
}

int	echo(char **arg)
{
	int i;
	int index;

	if (!arg)
		return (1); // add correct error code/message
	if (!ft_strncmp(arg[0], "echo", ft_strlen(arg[0])) && arg[1] == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	index = get_index_arg(arg);
	i = index;
	while (arg[i] != NULL)
	{
		if (index > 1)
		{
			ft_putstr_fd(arg[i], STDOUT_FILENO);
			
		}
		else
		{
			if (arg[i + 1] == NULL)
				ft_putendl_fd(arg[i], STDOUT_FILENO);
			else
			{
				ft_putstr_fd(arg[i], STDOUT_FILENO);
				ft_putchar_fd(' ', STDOUT_FILENO);
			}
		}
		i++;
	}
	return (0);
}

int	exec_echo(t_ast *cmd, char *envp[])
{
	char **args;

	args = extract_args(cmd);
	if (args)
	{
		echo(args);
		update_underscore(cmd, envp);
		//ft_free_2d_array(args);
		return (1);
	}
	else
	{
		//ft_free_2d_array(args);
		return (0); /// ??
	}
}

// int main()
// {
// 	char **arg = (char **)malloc(sizeof(char *) * 6);
//     arg[0] = ft_strdup("echo");
//     arg[1] = ft_strdup("-nnnn");
//     arg[2] = ft_strdup("hello");
//     arg[3] = ft_strdup("hello");
//     arg[4] = ft_strdup("world");
// 	arg[5] = NULL;

// 	echo(arg);
// }