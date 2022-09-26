/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 12:19:45 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/26 14:10:36 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "error_handling.h"
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
	char	*msg;

	msg = strerror(errno);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == ENOENT)
	{
		ft_putendl_fd(msg, STDERR_FILENO);
		exit(127);
	}
	else if (errno == EACCES)
	{
		ft_putendl_fd(msg, STDERR_FILENO);
		exit(126);
	}
}

void	cmd_custom_exit(char *cmd, int error_type)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (error_type == NOT_FOUND)
	{
		ft_putendl_fd("command not found", STDERR_FILENO);
		exit(127);
	}
	else if (error_type == IS_DIR)
	{
		ft_putendl_fd("is a directory", STDERR_FILENO);
		exit(126);
	}
}

void	dir_error_msg(t_ast *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->value, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd->next_sib_node->value, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

void	not_valid_identifier_msg(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}
