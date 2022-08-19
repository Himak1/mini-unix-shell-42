/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 16:06:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/19 15:01:00 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "utils.h"
#include "parser.h"
#include "lexer.h"
#include "builtins.h"
#include "expander.h"
}

TEST(update_underscore, basic_test1)
{
    char input[] = "echo hello world";

	t_token *lst;
	t_ast   *tree;
	char **envp = create_envp();

	lst = NULL;
	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	expand_tree(tree, envp);
    tree = tree->child_node->child_node;
    while (tree->type != CMD)
        tree->next_sib_node;
    
    int index = ft_get_index_2d(envp, "_=");
    ASSERT_STREQ(envp[index], "_=/usr/bin/env");
    update_underscore(tree, envp);
    ASSERT_STREQ(envp[index], "_=world");
}

TEST(update_underscore, basic_test2)
{
    char input[] = "ls -la";

	t_token *lst;
	t_ast   *tree;
	char **envp = create_envp();

	lst = NULL;
	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	expand_tree(tree, envp);
    tree = tree->child_node->child_node;
    while (tree->type != CMD)
        tree->next_sib_node;
    
    int index = ft_get_index_2d(envp, "_=");
    ASSERT_STREQ(envp[index], "_=/usr/bin/env");
    update_underscore(tree, envp);
    ASSERT_STREQ(envp[index], "_=-la");
}

TEST(update_underscore, env)
{
    char input[] = "env";

	t_token *lst;
	t_ast   *tree;
	char **envp = create_envp();

	lst = NULL;
	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	expand_tree(tree, envp);
    tree = tree->child_node->child_node;
    while (tree->type != CMD)
        tree->next_sib_node;
    
    int index = ft_get_index_2d(envp, "_=");
    ASSERT_STREQ(envp[index], "_=/usr/bin/env");
    update_underscore(tree, envp);
    ASSERT_STREQ(envp[index], "_=/usr/bin/env");
}