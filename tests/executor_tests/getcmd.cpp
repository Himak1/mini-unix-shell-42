/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getcmd.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 16:05:03 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/16 13:29:43 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
#include "executor.h"
#include "expander.h"
}

TEST(getcmd, basic)
{
	char 	input[] = "< infile cat < outfile";
	t_token *lst = nullptr;
	t_ast   *tree;

	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	ASSERT_TRUE(tree != nullptr);

	char	**cmd = getcmd(tree->child_node);
	EXPECT_STREQ(cmd[0], "cat");
}

TEST(getcmd, no_cmd)
{
	char 	input[] = "< infile < outfile";
	t_token *lst = nullptr;
	t_ast   *tree;

	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	ASSERT_TRUE(tree != nullptr);

	char	**cmd = getcmd(tree->child_node);
	EXPECT_EQ(cmd, nullptr);
}

TEST(getcmd, underscore)
{
	char 	input[] = "echo $_";
	t_token *lst = nullptr;
	t_ast   *tree;
	char **envp = create_envp();

	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	expand_tree(tree, envp);
	ASSERT_TRUE(tree != nullptr);

	char	**cmd = getcmd(tree->child_node);
	EXPECT_STREQ(cmd[0], "echo");
	EXPECT_STREQ(cmd[1], "/usr/bin/env");
}