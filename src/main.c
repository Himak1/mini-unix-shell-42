/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 11:38:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/17 16:14:24 by jhille        ########   odam.nl         */
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

static int	valid_syntax(t_data *data)
{
	int	exit_code;

	if (handle_all_heredocs(data) != -1)
	{
		expand_tree(data->tree, data->envv);
		exit_code = executor(data->tree, &data->envv);
	}
	else
		exit_code = -1;
	free_ast(data->tree);
	return (exit_code);
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
		line = readline("Minishell-$ ");
		add_history(line);
		ft_lexer(&data.lst, line);
		data.tree = parse_tokens(data.lst);
		ft_lstfree(data.lst);
		if (data.tree)
			data.exit_code = valid_syntax(&data);
		free(line);
	}
	rl_clear_history();
	return (0);
}
