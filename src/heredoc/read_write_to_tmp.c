/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_write_to_tmp.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:55:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/18 16:11:03 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "expander.h"

int	read_write_to_tmp(char *delimiter, int fd, char *envv[])
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline(">");
		if (!line)
			exit(EXIT_FAILURE);
		if (ft_strncmp(delimiter, line, delimiter_len) == 0)
			break ;
		expander(&line, envv);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}
