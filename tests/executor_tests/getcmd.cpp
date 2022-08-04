/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getcmd.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 16:05:03 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/03 17:05:10 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
#include "executor.h"
}

TEST(getcmd, basic)
{
	char 	input[] = "< infile cat < outfile";
	t_token *lst = nullptr;
	t_token *lst_head;
	t_ast   *tree;

	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	ASSERT_TRUE(tree != nullptr);

	char	**cmd = getcmd(tree->child_node);
	EXPECT_STREQ(cmd[0], "cat");
}

TEST(getcmd, no_cmd)
{
	char 	input[] = "< infile < outfile";
	t_token *lst = nullptr;
	t_token *lst_head;
	t_ast   *tree;

	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	ASSERT_TRUE(tree != nullptr);

	char	**cmd = getcmd(tree->child_node);
	EXPECT_EQ(cmd, nullptr);
}