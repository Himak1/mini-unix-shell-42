/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_write_to_tmp.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:55:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/13 13:47:18 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "expander.h"
#include "signal_handling.h"

void	read_write_to_tmp(char *delimiter, int fd, char *envv[])
{
	char				*line;
	struct sigaction	child_sigint_h;

	init_sigaction(&child_sigint_h, heredoc_interrupt);
	sigaction(SIGINT, &child_sigint_h, NULL);
	while (1)
	{
		line = readline(">");
		if (!line)
			exit(EXIT_FAILURE);
		if (ft_strncmp(delimiter, line, ft_strlen(line)) == 0)
			break ;
		expander(&line, envv);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
