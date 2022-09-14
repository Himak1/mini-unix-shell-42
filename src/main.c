/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 11:38:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/14 14:34:21 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "expander.h"
#include "heredoc.h"
#include "executor.h"
#include "signal_handling.h"
#include "minishell.h"

static void	copy_envp(t_data *data, char *envp[])
{
	t_uint	envp_size;
	t_uint	i;

	i = 0;
	envp_size = 0;
	while (envp[envp_size])
		envp_size++;
	data->envv = ft_xmalloc((envp_size + 1) * sizeof(char *));
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

	if (argc == 100 && argv[0][0])
		return (0); // filler
	copy_envp(&data, envp);
	init_sigaction(&data.sigint_h, prompt_interrupt);
	sigaction(SIGINT, &data.sigint_h, NULL);
	while (1)
	{
		data.lst = NULL;
		line = readline("Minishell:");
		ft_lexer(&data.lst, line);
		data.tree = parse_tokens(data.lst);
		ft_lstfree(data.lst);
		if (data.tree)
		{
			if (handle_all_heredocs(&data) != -1)
			{
				expand_tree(data.tree, data.envv);
				executor(data.tree, data.envv);
			}
			free_ast(data.tree);
		}
		free(line);
	}
	return (0);
}
