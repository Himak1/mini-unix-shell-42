/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 11:31:33 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/11 13:01:20 by jhille        ########   odam.nl         */
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