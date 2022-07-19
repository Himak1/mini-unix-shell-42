/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 11:31:33 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/19 13:25:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
}

// ---- input templates ---- //
t_token *create_list(void)
{
	t_token *t1;
	t_token *t2;
	t_token *t3;
	t_token *t4;

	t1 = lst_new(RDR_IN, ft_strdup("<"));
	t2 = lst_new(WORD, ft_strdup("infile"));
	t3 = lst_new(WORD, ft_strdup("echo"));
	t4 = lst_new(WORD, ft_strdup("hello"));
	lst_add_bk(&t1, t2);
	lst_add_bk(&t1, t3);
	lst_add_bk(&t1, t4);
	return (t1);
}

// ---- TESTS ---- //
TEST(exec_block, basic)
{
	t_token *input = create_list();
	t_token	*head = input;

	t_ast	*output = exec_block(&head);
	EXPECT_EQ(output->type, EXEC_BLOCK);
}

TEST(exec_block, only_rd)
{
	t_token	*t1 = lst_new(RDR_IN, ft_strdup("<"));
	t_token	*t2 = lst_new(WORD, ft_strdup("file"));
	t_token	*head = t1;
	lst_add_bk(&t1, t2);

	t_ast	*output = exec_block(&head);
	EXPECT_EQ(output->type, EXEC_BLOCK);
	EXPECT_EQ(output->child_node->type, RDS);
}

TEST(parse_pipe, basic)
{
	t_token	*t1 = lst_new(PIPE, ft_strdup("|"));
	t_token	*head = t1;

	t_ast	*output = parse_pipe(&head);
	EXPECT_EQ(output->type, TERMINAL);
	EXPECT_STREQ(output->value, "|");
}

/*
TEST(parser_token, basic)
{
	t_ast   *tree;
	t_token *list;

	list = create_list();
	tree = parse_tokens(&list);
	ASSERT_TRUE(tree->child_node != nullptr);
	EXPECT_TRUE(tree->child_node->next_sib_node == nullptr);
	EXPECT_STREQ(tree->child_node->child_node->child_node->child_node->child_node->child_node, "<");
}
*/
