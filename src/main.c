/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:37:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/08 16:55:52 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "utils.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"

static int	count_cmds(t_ast *tree)
{
	t_ast	*iter;
	int		i;

	i = 0;
	iter = tree->child_node;
	while (iter)
	{
		if (iter->type == EXEC_BLOCK)
			i++;
		iter = iter->next_sib_node;
	}
	return (i);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_token	*lst;
	t_token	*lst_head;
	t_ast	*tree;

	line = NULL;
	lst = NULL;
	if (argc == 100 && argv[0][0])
		return (0); // filler
	while (1)
	{
		line = readline("Minishell:");
		ft_lexer(&lst, line);
		lst_head = lst;
		tree = parse_tokens(&lst_head);
		executor(tree, count_cmds(tree), envp);
		free(line);
	}
	return (0);
}
