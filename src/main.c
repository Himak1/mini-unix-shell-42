/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 11:38:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/10/03 13:59:22 by jhille        ########   odam.nl         */
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

	if (!data->tree)
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		return (2);
	}
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
	if (exit_code == -1)
		return (1);
	return (exit_code);
}

static void	eof_handling(void)
{
	write(1, "exit\n", 6);
	exit(EXIT_SUCCESS);
}

int	line_only_whitespace(const char *line)
{
	t_uint	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	char	*line;

	(void)argv;
	(void)argc;
	shell_init(&data, envp);
	while (1)
	{
		data.lst = NULL;
		line = readline("minishell-$ ");
		if (!line)
			eof_handling();
		if (ft_strlen(line) != 0 && !line_only_whitespace(line))
		{
			add_history(line);
			ft_lexer(&data.lst, line);
			data.tree = parse_tokens(data.lst);
			if (data.lst)
				ft_lstfree(data.lst);
			g_exit_code = valid_syntax(&data);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
