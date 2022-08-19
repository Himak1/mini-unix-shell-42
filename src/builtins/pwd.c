/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 12:43:21 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/19 16:51:59 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "builtins.h"
#include <limits.h>

void pwd(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
}

int exec_pwd(t_ast *cmd, char *envp[])
{
	pwd();
	update_underscore(cmd, envp);
	return (0);
}

// int	pwd(void)
// {
// 	char	*env_var;

// 	env_var = getenv("PWD");
// 	if (env_var)
// 	{
// 		if (printf("%s", env_var) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// 	else
// 		return (-1);
// 	return (0);
// }
