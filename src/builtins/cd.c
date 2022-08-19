/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:34 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/19 19:20:24 by tvan-der      ########   odam.nl         */
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

int exec_cd(t_ast *cmd, char *envp[])
{
    int index;
    char **args;

    index = 0;
    args = extract_args(cmd);
    printf("args are:\n");
    while(*args)
    {
        printf("%s\n", *args);
        args++;
    }
    if (args)
	{
		cd(args);
		update_underscore(cmd, envp);
        index = ft_get_index_2d(envp, "PWD=");
        update_old_pwd(envp);
        update_pwd(getcwd(NULL, 0), envp);
		//ft_free_2d_array(args);
		return (1);
	}
	else
	{
		//ft_free_2d_array(args);
		return (0); /// ??
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