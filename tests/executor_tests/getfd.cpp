/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getfd.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:36:36 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/15 11:57:58 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
#include "executor.h"
}

TEST(getfd, basic)
{
	char 	input[] = "< infile cat < outfile";
	t_token *lst = nullptr;
	t_ast   *tree;

	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	ASSERT_TRUE(tree != nullptr);

	EXPECT_EQ(getfd_in(tree->child_node), -1);
}

TEST(getfd, issue)
{
	char 	input[] = "echo yeet";
	t_token *lst = nullptr;
	t_ast   *tree;

	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	ASSERT_TRUE(tree != nullptr);

	EXPECT_EQ(getfd_in(tree->child_node), 0);
}

TEST(getfd, no_redirect)
{
	char 	input[] = "cat infile";
	t_token *lst = nullptr;
	t_ast   *tree;

	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	ASSERT_TRUE(tree != nullptr);

	EXPECT_EQ(getfd_in(tree->child_node), 0);
}
