/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 11:38:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/15 17:20:48 by tvan-der      ########   odam.nl         */
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

// static int	count_cmds(t_ast *tree)
// {
// 	t_ast	*iter;
// 	int		i;

// 	i = 0;
// 	iter = tree->child_node;
// 	while (iter)
// 	{
// 		if (iter->type == EXEC_BLOCK)
// 			i++;
// 		iter = iter->next_sib_node;
// 	}
// 	return (i);
// }

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*line;
// 	t_token	*lst;
// 	t_token	*lst_head;
// 	t_ast	*tree;

// 	line = NULL;
// 	lst = NULL;
// 	if (argc == 100 && argv[0][0])
// 		return (0); // filler
// 	while (1)
// 	{
// 		line = readline("Minishell:");
// 		ft_lexer(&lst, line);
// 		lst_head = lst;
// 		tree = parse_tokens(&lst_head);
// 		executor(tree, count_cmds(tree), envp);
// 		free(line);
// 	}
// 	return (0);
// }
