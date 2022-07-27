/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmds.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/27 15:28:04 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executor.h"

int execute_cmds(t_ast *ast)
{
	t_ast	iter;
	int		pid;
	int		fork[]

	pid = 0;
	iter = ast->child_node;
	while (iter != NULL)
	{
		pid = fork();
		if (pid == 0)
			break ;
		
	}
}
