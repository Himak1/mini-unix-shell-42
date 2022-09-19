/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_write_to_tmp.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:55:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/19 15:39:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "expander.h"
#include "signal_handling.h"

void	read_write_to_tmp(char *delimiter, int file_fd, char *envv[])
{
	char				*line;
	struct sigaction	child_sigint_h;
	t_uint				linelen;

	init_sigaction(&child_sigint_h, heredoc_interrupt);
	sigaction(SIGINT, &child_sigint_h, NULL);
	while (1)
	{
		line = readline(">");
		if (!line)
			exit(EXIT_FAILURE);
		linelen = ft_strlen(line);
		if (linelen != 0 && ft_strncmp(delimiter, line, linelen) == 0)
			break ;
		if (linelen != 0)
			expander(&line, envv);
		write(file_fd, line, ft_strlen(line));
		write(file_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(file_fd);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
