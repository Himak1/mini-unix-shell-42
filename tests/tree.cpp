/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 16:55:08 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/05 17:14:58 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
}

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
}

TEST(add_child, basic)
{
	t_ast	*p = new_node(EXE_CHAIN);
	t_ast	*c1 = new_node(BASE);
	t_ast	*c2 = new_node(ADD_BASE);

	add_child(p, c1);
	add_child(p, c2);
	EXPECT_EQ(p->child_node->type, BASE);
	EXPECT_EQ(p->child_node->next_sib_node->type, ADD_BASE);
}
