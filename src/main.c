/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 11:38:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/22 13:38:22 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "expander.h"
#include "builtins.h"
#include "heredoc.h"
#include "executor.h"
#include "signal_handling.h"
#include "shell_init.h"
#include "minishell.h"

int	g_exit_code = 0;

int	valid_syntax(t_data *data)
{
	int	exit_code;

	if (handle_all_heredocs(data) != -1)
	{
		signal(SIGINT, SIG_IGN);
		exit_code = expand_tree(data->tree, data->envv);
		if (exit_code >= 0)
			exit_code = executor(data->tree, &data->envv);
		if (exit_code == 131)
			write(1, "Quit: 3\n", 8);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->config);
	}
	else
		exit_code = -1;
	free_ast(data->tree);
	sigaction(SIGINT, &data->sigint_h, NULL);
	return (exit_code);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	char	*line;

	if (argc == 100 && argv[0][0])
		return (0); // filler
	shell_init(&data, envp);
	while (1)
	{
		data.lst = NULL;
		line = readline("minishell-$ ");
		if (!line)
		{
			write(1, "exit\n", 6);
			exit(EXIT_SUCCESS);
		}
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			ft_lexer(&data.lst, line);
			data.tree = parse_tokens(data.lst);
			ft_lstfree(data.lst);
			if (data.tree)
				g_exit_code = valid_syntax(&data);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
