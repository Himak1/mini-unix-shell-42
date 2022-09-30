/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:34 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/30 15:44:40 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include "error_handling.h"
#include <stdio.h>
#include <readline/readline.h>

static char	*ft_getenv_path(char *envv[], char *var_name)
{
	char	*var;
	char	*tmp;
	char	*path_only;

	var = ft_getenv(envv, var_name);
	tmp = NULL;
	path_only = NULL;
	if (var)
	{
		tmp = ft_strchr(var, '=');
		if (tmp)
			path_only = ft_strdup(tmp + 1);
	}
	return (path_only);
}

int	cd(t_ast *cmd, char *envv[])
{
	char	*dir;

	dir = NULL;
	if (cmd->next_sib_node)
	{
		dir = cmd->next_sib_node->value;
		if (!ft_strncmp(dir, "~", ft_strlen(dir)))
			chdir(ft_getenv_path(envv, "HOME"));
		else if (!ft_strncmp(dir, "-", ft_strlen(dir)))
			chdir(ft_getenv_path(envv, "OLDPWD"));
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
		chdir(ft_getenv_path(envv, "HOME"));
	return (0);
}

int	exec_cd(t_ast *cmd, char **envv[])
{
	int	exit_code;

	exit_code = cd(cmd, *envv);
	update_underscore(cmd, envv);
	update_old_pwd(envv);
	update_pwd(*envv);
	return (exit_code);
}
