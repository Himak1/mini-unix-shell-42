/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 12:43:21 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/23 15:47:10 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "builtins.h"

void	pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
}

int	exec_pwd(t_ast *cmd, char **envv[])
{
	pwd();
	update_underscore(cmd, envv);
	return (0);
}
