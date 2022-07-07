/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 11:31:33 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/07 18:21:39 by jhille        ########   odam.nl         */
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
}

// ---- TESTS ---- //

TEST(next_2_tkn, basic)
{
	t_token	*lst = create_list();

	ASSERT_EQ(lst->type, RDR_IN);
	ASSERT_EQ(next_2_tkn(lst, RDR_IN, WORD), 1);
}

TEST(rd_in, basic)
{
	int		status = 0;
	t_token	*t1 = lst_new(RDR_IN, ft_strdup("<"));
	t_token	*t2 = lst_new(WORD, ft_strdup("infile"));
	t_token	*head = t1;
	t1->next = t2;

	t_ast	*output = rd_in(&head, &status);
	/*
	ASSERT_TRUE(output);
	EXPECT_TRUE(output->child_node != nullptr);
	EXPECT_TRUE(output->child_node->next_sib_node != nullptr);
	EXPECT_STREQ(output->child_node->value, "<");
	EXPECT_STREQ(output->child_node->next_sib_node->value, "infile");
	*/
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