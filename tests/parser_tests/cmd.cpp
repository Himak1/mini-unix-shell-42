/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:37:08 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/17 13:55:26 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
}

// ---- input template ---- //
t_token *create_list(char *str1, char *str2, char *str3, char *str4)
{
	t_token *t1;
	t_token *t2;
	t_token *t3;
	t_token *t4;

	t1 = lst_new(WORD, ft_strdup(str1));
	t2 = lst_new(WORD, ft_strdup(str2));
	t3 = lst_new(WORD, ft_strdup(str3));
	t4 = lst_new(WORD, ft_strdup(str4));
	lst_add_bk(&t1, t2);
	lst_add_bk(&t1, t3);
	lst_add_bk(&t1, t4);
	return (t1);
}

// ---- TESTS ---- //
TEST(parse_cmd, basic)
{
	t_token *list = create_list("echo", "hello", "world", "yeet");
	t_token	*head = list;

	t_ast	*output = new_node(EXEC_BLOCK);
	while (head)
		parse_cmd(output, &head);
	EXPECT_EQ(output->child_node->type, CMD);
	EXPECT_STREQ(output->child_node->child_node->value, "echo");
	EXPECT_STREQ(output->child_node->child_node->next_sib_node->value, "hello");
	EXPECT_STREQ(output->child_node->child_node->next_sib_node->next_sib_node->value, "world");
	EXPECT_STREQ(output->child_node->child_node->next_sib_node->next_sib_node->next_sib_node->value, "yeet");
	ft_lstfree(list);
	free_ast(output);
}

TEST(parse_cmd, shuffled_cmd)
{
	t_token *list = create_list("echo", "hello", "world", "yeet");
	t_token	*rds = lst_new(RDR_IN, ft_strdup("<"));
	lst_add_ft(&list, rds);
	t_token	*head = list;

	t_ast	*output = new_node(EXEC_BLOCK);
	parse_cmd(output, &head);
	parse_cmd(output, &head);
	parse_cmd(output, &head);
	parse_cmd(output, &head);
	parse_cmd(output, &head);

	EXPECT_EQ(output->child_node->type, CMD);
	EXPECT_EQ(output->child_node->next_sib_node, nullptr);
	ft_lstfree(list);
	free_ast(output);
}
