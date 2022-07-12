/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/08 15:19:16 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/12 14:25:17 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
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
TEST(rd_in, basic)
{
	int		status = 0;
	t_token	*t1 = create_list();
	t_token	*head = t1;

	t_ast	*output = rd_in(&head, &status);
	ASSERT_TRUE(output);
	EXPECT_TRUE(output->child_node != nullptr);
	EXPECT_TRUE(output->child_node->next_sib_node != nullptr);
	EXPECT_STREQ(output->child_node->value, "<");
	EXPECT_STREQ(output->child_node->next_sib_node->value, "infile");
}

TEST(rds, basic)
{
	int		status = 0;
	t_token	*t1 = create_list();
	t_token	*head = t1;

	t_ast	*output = rds(&head, &status);
	ASSERT_TRUE(output);
	EXPECT_EQ(output->child_node->type, RD_IN);
}
