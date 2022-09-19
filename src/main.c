/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 11:38:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/19 17:41:46 by jhille        ########   odam.nl         */
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

static void	set_termios(t_data *data)
{
	tcgetattr(STDIN_FILENO, &data->config);
	data->config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->config);
}

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
		signal(SIGINT, SIG_IGN);
		expand_tree(data->tree, data->envv);
		exit_code = executor(data->tree, &data->envv);
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
	copy_envp(&data, envp);
	signals_on_init(&data);
	set_termios(&data);
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
				data.exit_code = valid_syntax(&data);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
