/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:37:08 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/11 15:50:53 by jhille        ########   odam.nl         */
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

	t1 = lst_new(WORD, ft_strdup("echo"));
	t2 = lst_new(WORD, ft_strdup("hello"));
	t3 = lst_new(WORD, ft_strdup("world"));
	t4 = lst_new(WORD, ft_strdup("yeet"));
	lst_add_bk(&t1, t2);
	lst_add_bk(&t1, t3);
	lst_add_bk(&t1, t4);
	return (t1);
}

TEST(cmd, basic)
{
	t_token *list = create_list();
	t_token	*head = list;
	int		status = 0;

	t_ast	*output = cmd(&head, &status);
	EXPECT_EQ(output->type, CMD);
	EXPECT_STREQ(output->child_node->value, "echo");
	EXPECT_STREQ(output->child_node->next_sib_node->value, "hello");
	EXPECT_STREQ(output->child_node->next_sib_node->next_sib_node->value, "world");
	EXPECT_STREQ(output->child_node->next_sib_node->next_sib_node->next_sib_node->value, "yeet");
}
