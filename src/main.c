/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:37:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/20 14:41:38 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int	main(void)
{
	char	*ptr;

	ptr = NULL;
	while (1)
	{
		ptr = readline("Minishell:");
		printf("%s\n", ptr);
		free(ptr);
	}
	return (0);
}
