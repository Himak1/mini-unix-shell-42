/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:08:34 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/17 19:01:42 by tvan-der      ########   odam.nl         */
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

// char **add_oldpwd(char *envp[])
// {
//     int i;
//     int j;
//     int position;
//     char **new_envp;
    
//     i = 0;
//     while (envp[i] != NULL)
//         i++;
//     new_envp = (char **)malloc(sizeof(char *) * (i + 2));
//     position = ft_get_index_2d(envp, "ZDOTDIR=");
//     i = 0;
//     j = 0;
//     while (envp[i] != NULL)
//     {
//         if (i == position)
//         {
//             new_envp[j] = ft_strdup("OLDPWD=");
//             j++;
//         }
//         new_envp[j] = ft_strdup(envp[i]);
//         i++;
//         j++;
//     }
//     new_envp[i] = NULL;
//     ft_free_2d_array(envp);
//     return (new_envp);
// }

void cd(t_ast *cmd)
{
    char *dir;
    //char cwd[256];

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
                //printf("hi\n");
                perror("Error"); // fix error message
            }
        }
    }
    else
        chdir(getenv("HOME"));
    //printf("dir is %s\n", getcwd(cwd, sizeof(cwd)));
}

int exec_cd(t_ast *cmd, char **envv[])
{
    cd(cmd);
    update_underscore(cmd, envv);
    update_old_pwd(envv);
    update_pwd(*envv);
    return (0);
}

