/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 11:33:51 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/22 13:41:55 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "signal_handling.h"

extern int	g_exit_code;

void	init_sigaction(struct sigaction *sa, void (*handler)(int))
{
	sa->sa_handler = handler;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
}

void	prompt_interrupt(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
	}
}

void	heredoc_interrupt(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_clear_history();
		rl_on_new_line();
		exit(EXIT_FAILURE);
	}
}

void	signals_on_init(t_data *data)
{
	init_sigaction(&data->sigint_h, prompt_interrupt);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &data->sigint_h, NULL);
}
