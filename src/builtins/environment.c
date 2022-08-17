/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 13:24:09 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/17 15:02:12 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"

//initalizing enviroment in shell.
//creating linked list and key and value

// NOTE:
// OLWDPWD --> missing in list (comes between ZDOTDIR & ORIGINAL_XDG..)
// init _=


char	**env_init(char **envp)
{
	char **mini_envp;
	
	return (mini_envp);
}

int main (int argc, char **argv, char **envp)
{
    t_env_var;

	mini_envp = env_init(envp);
	while (*mini_envp != NULL)
	{
		ft_putstr_fd(*mini_envp, STDOUT_FILENO);
		mini_envp++;
	}
	return (0);
}