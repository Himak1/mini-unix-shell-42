/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_parser_integration.cpp                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 14:54:28 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/16 14:23:03 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
#include "parser.h"
#include "expander.h"
}

// ---- Testing 


// ---- Tests ---- //

TEST(lexer_parser, basic1)
{
	char input[] = "echo hello world";

	t_token *lst;

	t_ast   *tree;

	lst = NULL;
	ft_lexer(&lst, input);
	tree = parse_tokens(lst); 
	EXPECT_TRUE(tree != nullptr);
	EXPECT_EQ(tree->child_node->type, EXEC_BLOCK);
	EXPECT_EQ(tree->child_node->child_node->type, CMD);
	EXPECT_EQ(tree->child_node->child_node->child_node->type, TERMINAL);
	EXPECT_STREQ(tree->child_node->child_node->\
				child_node->next_sib_node->value, "hello");
	EXPECT_STREQ(tree->child_node->child_node->child_node->\
				next_sib_node->next_sib_node->value, "world");
	//lst_clear(lst);
	//free_ast(tree);
	ft_lstfree(lst);
	free_child_nodes(tree);
}

TEST(lexer_parser, 2_commands_with_pipe)
{
	char input[] = "echo hello world | cat yeet";

	t_token *lst;
	t_ast   *tree;

	lst = NULL;
	ft_lexer(&lst, input);
	tree = parse_tokens(lst);
	EXPECT_TRUE(tree != nullptr);
	EXPECT_EQ(tree->child_node->type, EXEC_BLOCK);
	EXPECT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	EXPECT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
	// lst_clear(lst);
	// free_ast(tree);
	ft_lstfree(lst);
	free_child_nodes(tree);
}

TEST(lexer_parser, invalid_pipe)
{
	char 	input[] = "|";
	t_token *lst = nullptr;
	t_ast   *tree;

	ft_lexer(&lst, input);
	EXPECT_EQ(lst->type, PIPE);

	tree = parse_tokens(lst);
	EXPECT_EQ(tree, nullptr);
	// lst_clear(lst);
	ft_lstfree(lst);
}

TEST(lexer_parser, lots_of_rds)
{
	char	input[] = "< infile < infile > outfile";
	t_token *lst = nullptr;
	t_ast   *tree;

	ft_lexer(&lst, input);
	EXPECT_EQ(lst->type, RDR_IN);

	tree = parse_tokens(lst);
	ASSERT_TRUE(tree != nullptr);
	EXPECT_EQ(tree->child_node->child_node->type, RDS);
	// lst_clear(lst);
	// free_ast(tree);
	ft_lstfree(lst);
	free_child_nodes(tree);
}

/*
TEST(lexer_parser, valid_command_invalid_pipe)
{
	char	input[] = "cat generic-file |";
	t_token *lst = nullptr;
	t_token *lst_head;
	t_ast   *tree;

	ft_lexer(&lst, input);
	EXPECT_EQ(lst->type, WORD);

	lst_head = lst;
	tree = parse_tokens(&lst_head);
	EXPECT_EQ(tree, nullptr);
}
*/

TEST(lexer_parser, single_cmd)
{
	char	input[] = "hello";
	t_token *lst = nullptr;
	t_ast   *tree;

	ft_lexer(&lst, input);
	EXPECT_EQ(lst->type, WORD);

	tree = parse_tokens(lst);
	EXPECT_TRUE(tree != nullptr);
	// lst_clear(lst);
	// free_ast(tree);
	ft_lstfree(lst);
	free_child_nodes(tree);
}
