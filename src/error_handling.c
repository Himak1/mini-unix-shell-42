/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 12:19:45 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/21 14:42:04 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "utils.h"

void	sh_error(void)
{
	char	*errorstr;

	errorstr = strerror(errno);
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, errorstr, ft_strlen(errorstr));
}

void	cmd_error_exit(char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	if (errno == ENOENT)
	{
		write(STDERR_FILENO, ": command not found\n", 20);
		exit(127);
	}
	else if (errno == EACCES)
	{
		write(STDERR_FILENO, ": Permission denied\n", 20);
		exit(126);
	}
}
