/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_pars_exp_integration.cpp                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:35:12 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/05 11:55:19 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "lexer.h"
}

TEST(lexer_parser_expander, basic_no_env)
{
	char input[] = "echo hello world";

	t_token *lst;
	t_token *lst_head;

	t_ast   *tree;

	char **envp = create_envp();

	lst = NULL;
	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	expand_tree(tree, envp);
	EXPECT_TRUE(tree != nullptr);
	EXPECT_EQ(tree->child_node->type, EXEC_BLOCK);
	EXPECT_EQ(tree->child_node->child_node->type, CMD);
	EXPECT_EQ(tree->child_node->child_node->child_node->type, TERMINAL);
	EXPECT_STREQ(tree->child_node->child_node->\
				child_node->next_sib_node->value, "hello");
	EXPECT_STREQ(tree->child_node->child_node->child_node->\
				next_sib_node->next_sib_node->value, "world");
}

TEST(lexer_parser_expander, basic_with_env)
{
	char input[] = "echo hello $PWD";

	t_token *lst;
	t_token *lst_head;

	t_ast   *tree;

	char **envp = create_envp();

	lst = NULL;
	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	expand_tree(tree, envp);
	EXPECT_TRUE(tree != nullptr);
	EXPECT_EQ(tree->child_node->type, EXEC_BLOCK);
	EXPECT_EQ(tree->child_node->child_node->type, CMD);
	EXPECT_EQ(tree->child_node->child_node->child_node->type, TERMINAL);
	EXPECT_STREQ(tree->child_node->child_node->\
				child_node->next_sib_node->value, "hello");
	EXPECT_STREQ(tree->child_node->child_node->child_node->\
				next_sib_node->next_sib_node->value, "/pwd/desktop/minishell");
}

TEST(lexer_parser, 2_commands_with_pipe_no_env)
{
	char input[] = "echo hello world | cat yeet";

	t_token *lst;
	t_token *lst_head;
	t_ast   *tree;

	lst = NULL;
	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	EXPECT_TRUE(tree != nullptr);
	EXPECT_EQ(tree->child_node->type, EXEC_BLOCK);
	EXPECT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	EXPECT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
}

TEST(lexer_parser, 2_commands_with_pipe_with_env1)
{
	char input[] = "echo hello world | \"cat\" yeet";

	t_token *lst;
	t_token *lst_head;
	t_ast   *tree;

	lst = NULL;
	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	EXPECT_TRUE(tree != nullptr);
	EXPECT_EQ(tree->child_node->type, EXEC_BLOCK);
	EXPECT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	EXPECT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
}

TEST(lexer_parser, 2_commands_with_pipe_with_env2)
{
	char input[] = "echo hello world | cat \"yeet $PATH\"";

	t_token *lst;
	t_token *lst_head;
	t_ast   *tree;

	lst = NULL;
	ft_lexer(&lst, input);
	lst_head = lst;
	tree = parse_tokens(&lst_head);
	EXPECT_TRUE(tree != nullptr);
	EXPECT_EQ(tree->child_node->type, EXEC_BLOCK);
	EXPECT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	EXPECT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
}
