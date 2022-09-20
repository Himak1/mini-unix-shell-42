/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 12:19:45 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/20 13:16:27 by jhille        ########   odam.nl         */
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

void	cmd_error(char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
}
