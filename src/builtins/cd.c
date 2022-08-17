/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:34 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/17 16:27:03 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include <stdio.h>
#include <readline/readline.h>

//   cd (change directory)
//   -----------------------------------------------------
//   -> change to path, absolute path, relative path
//   -> change current directory to parent directory

//   chdir()
//   ----------------------------------------------------
//   int chdir(const char *path);
//   char *getcwd(char *buf, size_t size);


//   parameter --> array of arrays
//   ["cd", "/usr/desktop"]
//   ["cd", "desktop"]
//   ["cd", ".."]

void cd(char **arg)
{
    if (arg[1] ==  NULL || !ft_strncmp(arg[1], "~", ft_strlen(arg[1])))
        chdir(getenv("HOME"));
    else if (!ft_strncmp(arg[1], "-", ft_strlen(arg[1])))
        chdir(getenv("OLDPWD"));
    else
    {
        if (chdir(arg[1]) != 0)
            perror("Error");
    }
}

/*
int main(int argc, char **argv, char **envp)
{
    char *line;
    char **arg;
    
    printf("%d & %s\n", argc, argv[0]);
    while (1)
	{
		line = readline("> ");
        arg = ft_split(line, ' ');
        if (ft_strncmp(arg[0], "cd", ft_strlen(arg[0])) == 0)
            cd(arg);
        else if (ft_strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0)
            pwd();
        else if (ft_strncmp(arg[0], "env", ft_strlen(arg[0])) == 0)
            print_env(envp);
	}
}
*/