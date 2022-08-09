/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getfd.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 14:36:36 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/04 18:05:44 by jhille        ########   odam.nl         */
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
	t_token *lst_head;
	t_ast   *tree;

	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	ASSERT_TRUE(tree != nullptr);

	EXPECT_EQ(getfd(tree->child_node, RD_IN), -1);
}

TEST(getfd, issue)
{
	char 	input[] = "echo yeet";
	t_token *lst = nullptr;
	t_token *lst_head;
	t_ast   *tree;

	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	ASSERT_TRUE(tree != nullptr);

	EXPECT_EQ(getfd(tree->child_node, RD_IN), 0);
}

TEST(getfd, no_redirect)
{
	char 	input[] = "cat infile";
	t_token *lst = nullptr;
	t_token *lst_head;
	t_ast   *tree;

	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	ASSERT_TRUE(tree != nullptr);

	EXPECT_EQ(getfd(tree->child_node, RD_IN), 0);
}
