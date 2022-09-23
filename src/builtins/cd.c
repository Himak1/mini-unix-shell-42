/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:34 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/23 12:01:20 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include "error_handling.h"
#include <stdio.h>
#include <readline/readline.h>

int	cd(t_ast *cmd)
{
	char	*dir;

	dir = NULL;
	if (cmd->next_sib_node)
	{
		dir = cmd->next_sib_node->value;
		if (!ft_strncmp(dir, "~", ft_strlen(dir)))
			chdir(getenv("HOME"));
		else if (!ft_strncmp(dir, "-", ft_strlen(dir)))
			chdir(getenv("OLDPWD"));
		else
		{
			if (chdir(dir) != 0)
			{
				dir_error_msg(cmd);
				return (EXIT_FAILURE);
			}
		}
	}
	else
		chdir(getenv("HOME"));
	return(0);
}

int	exec_cd(t_ast *cmd, char **envv[])
{
	int	exit_code;

	exit_code = cd(cmd);
	update_underscore(cmd, envv);
	update_old_pwd(envv);
	update_pwd(*envv);
	return (exit_code);
}
