/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_write_to_tmp.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:55:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/12 14:11:05 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "expander.h"
#include "signal_handling.h"

int	read_write_to_tmp(char *delimiter, int fd, char *envv[])
{
	char				*line;
	struct sigaction	sa;

	sa.sa_handler = heredoc_interrupt;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
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
	exit(EXIT_SUCCESS);
	return (0);
}
