/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 13:24:09 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/18 12:22:14 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"

// initalizing enviroment in shell.
// make a copy of the envp received through the main
// do not add OLDPWD (only included after changing directory)
// at initalization, '_' key should be below PATH (after the first command called after, it moves to the bottom.)
// -----> only if env is the FIRST command





char	**env_init(char **envp)
{
	char **mini_envp;
	
	
	return (mini_envp);
}

void	print_envp(char *envp)
{
	while (*envp != NULL)
	{
		ft_putstr_fd(*envp, STDOUT_FILENO);
		envp++;
	}
}

int main (int argc, char **argv, char **envp)
{
	char **mini_envp;
	
	mini_envp = copy(envp);
	print_envp(mini_envp);
	return (0);
}