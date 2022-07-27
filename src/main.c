/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:37:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/26 14:43:38 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "utils.h"
#include "builtins.h"

int	main(int argc, char *argv[])
{
	char	*ptr;

	ptr = NULL;
	if (argc == 100 && argv[0][0])
		return (0); // filler
	while (1)
	{
		ptr = readline("Minishell:");
		if (!ft_strncmp(ptr, "pwd", 3))
			pwd();
		printf("\n");
		free(ptr);
	}
	return (0);
}
