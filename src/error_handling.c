/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 12:19:45 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/23 19:45:10 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parser.h"

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

void	dir_error_msg(t_ast *cmd)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd->value, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd->next_sib_node->value, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

void	not_valid_identifier_msg(char *str)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}
