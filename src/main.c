/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 11:38:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/15 14:19:50 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "lexer.h"
#include "expander.h"
#include "executor.h"
#include "minishell.h"

static int	count_cmds(t_ast *tree)
{
	t_ast	*iter;
	int		i;

	i = 0;
	iter = tree->child_node;
	while (iter)
	{
		if (iter->type == EXEC_BLOCK)
			i++;
		iter = iter->next_sib_node;
	}
	return (i);
}

static void	copy_envp(t_data *data, char *envp[])
{
	t_uint	envp_size;
	t_uint	i;

	i = 0;
	envp_size = 0;
	while (envp[envp_size])
		envp_size++;
	data->envv = xmalloc((envp_size + 1) * sizeof(char *));
	while (envp[i])
	{
		data->envv[i] = ft_strdup(envp[i]);
		if (!data->envv[i])
			exit(EXIT_FAILURE);
		i++;
	}
	data->envv[i] = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	char	*line;

	line = NULL;
	if (argc == 100 && argv[0][0])
		return (0); // filler
	copy_envp(&data, envp);
	// print_envp(data.envv);
	while (1)
	{
		data.lst = NULL;
		line = readline("Minishell:");
		ft_lexer(&data.lst, line);
		data.tree = parse_tokens(data.lst);
		ft_lstfree(data.lst);
		if (data.tree)
		{
			expand_tree(data.tree, data.envv);
			executor(data.tree->child_node, count_cmds(data.tree), data.envv);
			free_ast(data.tree);
		}
		free(line);
	}
	return (0);
}
