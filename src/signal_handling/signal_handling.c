/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 11:33:51 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/12 14:01:08 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "signal_handling.h"

void	prompt_interrupt(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_interrupt(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		exit(EXIT_FAILURE);
	}
}
