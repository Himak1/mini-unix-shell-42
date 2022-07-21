/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 14:27:25 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/21 16:28:06 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdio.h>
/*

1.	look if there is a $
*/

// void	find_env_var()
// {
	
// }

void	expand_dollar_sign(char *value, char)
{
	if (!value)
		return ;
	while(*value)
	{
		
	}
}

char	**create_envp()
{
	char **envp = NULL;
		envp = (char **)malloc((12) * sizeof(char *));
	envp[0] = ft_strdup("CHARSET=UTF-8");
	envp[1] = ft_strdup("HOSTNAME=a4d647f5f42a");
	envp[2] = ft_strdup("PWD=/pwd/desktop/minishell");
	envp[3] = ft_strdup("HOME=/root");
	envp[4] = ft_strdup("LANG=C.UTF-8");
	envp[5] = ft_strdup("TERM=xterm");
	envp[6] = ft_strdup("SHLVL=2");
	envp[7] = ft_strdup("LC_COLLATE=C");
	envp[8] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	envp[9] = ft_strdup("OLDPWD=/pwd/desktop/minishell/build");
	envp[10] = ft_strdup("_=/usr/bin/env");
	envp[11] = NULL;
	
	return (envp);
}

// void	expand_double_quote(char *value)
// {
	
// }

// void	expander(t_ast **tree)
// {
	
// }