/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_functions.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 14:27:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/19 15:44:58 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
}

// -- input -- //
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
TEST(new_node, basic)
{
	t_ast	*ptr;

	ptr = new_node(BASE);
	ASSERT_TRUE(ptr != NULL);
	EXPECT_EQ(ptr->type, BASE);
	EXPECT_EQ(ptr->num_children, 0);
	EXPECT_EQ(ptr->value, nullptr);
	EXPECT_EQ(ptr->child_node, nullptr);
	EXPECT_EQ(ptr->next_sib_node, nullptr);
	EXPECT_EQ(ptr->prev_sib_node, nullptr);
	free(ptr);
}

TEST(add_child, basic)
{
	t_ast	*p = new_node(EXEC_CHAIN);
	t_ast	*c1 = new_node(BASE);
	t_ast	*c2 = new_node(ADD_BASE);

	add_child(p, c1);
	add_child(p, c2);
	EXPECT_EQ(p->child_node->type, BASE);
	EXPECT_EQ(p->child_node->next_sib_node->type, ADD_BASE);
	free_child_nodes(p);
	free(p);
	
}

TEST(add_child, reverse_traversible_list)
{
	t_ast	*t1 = new_node(RDS);
	add_child(t1, new_node(RD_IN));
	add_child(t1, new_node(RD_OUT));
	add_child(t1, new_node(RD_AP));
	add_child(t1, new_node(RD_DE));

	t_ast	*iter = t1->child_node;
	while (iter->next_sib_node)
		iter = iter->next_sib_node;
	EXPECT_EQ(iter->type, RD_DE);
	while (iter->prev_sib_node)
		iter = iter->prev_sib_node;
	EXPECT_EQ(iter->type, RD_IN);
	free_child_nodes(t1);
	free(t1);
}