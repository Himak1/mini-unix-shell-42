/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:09:10 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/16 15:38:21 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include <stdio.h>

void print_env(char **envp)
{
    while (*envp != NULL)
    {
        printf("%s\n", *envp);
        envp++;
    }
}
