/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_pars_exp_integration.cpp                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:35:12 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/12 13:07:44 by tvan-der      ########   odam.nl         */
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
	char input[] = "< infile cat | wc -l";

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
	ASSERT_EQ(tree->type, EXEC_CHAIN);
	
	ASSERT_EQ(tree->child_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->child_node->type, RDS);
	ASSERT_EQ(tree->child_node->child_node->next_sib_node->type, CMD);
	ASSERT_EQ(tree->child_node->child_node->next_sib_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->next_sib_node->child_node->value, "cat");
	ASSERT_EQ(tree->child_node->child_node->child_node->type, RD_IN);
	ASSERT_EQ(tree->child_node->child_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->child_node->value, "<");
	ASSERT_EQ(tree->child_node->child_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->child_node->next_sib_node->value, "infile");
	
	ASSERT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->value, "|");
	
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->value, "wc");
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->value, "-l");
	
}

TEST(lexer_parser, 2_commands_with_pipe_with_env1)
{
	char input[] = "echo hello world | \"cat\" yeet";

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
	ASSERT_EQ(tree->type, EXEC_CHAIN);

	ASSERT_EQ(tree->child_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->value, "echo");
	ASSERT_EQ(tree->child_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->next_sib_node->value, "hello");
	ASSERT_EQ(tree->child_node->child_node->child_node->next_sib_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->next_sib_node->next_sib_node->value, "world");
	
	ASSERT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->value, "|");
	
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->value, "cat");
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->value, "yeet");
}

TEST(lexer_parser, 2_commands_with_pipe_with_env2)
{
	char input[] = "echo hello world | \"cat\" $PWD";

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
	ASSERT_EQ(tree->type, EXEC_CHAIN);

	ASSERT_EQ(tree->child_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->value, "echo");
	ASSERT_EQ(tree->child_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->next_sib_node->value, "hello");
	ASSERT_EQ(tree->child_node->child_node->child_node->next_sib_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->next_sib_node->next_sib_node->value, "world");
	
	ASSERT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->value, "|");
	
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->value, "cat");
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->value, "/pwd/desktop/minishell");
}

TEST(lexer_parser, 2_commands_with_pipe_with_env3)
{
	char input[] = "echo hello world | cat \"hello i am currently in $PWD\"";

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
	ASSERT_EQ(tree->type, EXEC_CHAIN);

	ASSERT_EQ(tree->child_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->value, "echo");
	ASSERT_EQ(tree->child_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->next_sib_node->value, "hello");
	ASSERT_EQ(tree->child_node->child_node->child_node->next_sib_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->next_sib_node->next_sib_node->value, "world");
	
	ASSERT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->value, "|");
	
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->value, "cat");
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->value, "hello i am currently in /pwd/desktop/minishell");
}

TEST(lexer_parser, 3_commands_with_pipe_with_env1)
{
	char input[] = "echo hello world | cat \"hello i am currently in $PWD\" | echo \"bye now $ $USER $LANG\"";

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
	ASSERT_EQ(tree->type, EXEC_CHAIN);

	ASSERT_EQ(tree->child_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->value, "echo");
	ASSERT_EQ(tree->child_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->next_sib_node->value, "hello");
	ASSERT_EQ(tree->child_node->child_node->child_node->next_sib_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->child_node->child_node->next_sib_node->next_sib_node->value, "world");
	
	ASSERT_EQ(tree->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->value, "|");
	
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->value, "cat");
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->value, "hello i am currently in /pwd/desktop/minishell");

	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->next_sib_node->value, "|");
	
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->next_sib_node->next_sib_node->type, EXEC_BLOCK);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->next_sib_node->next_sib_node->child_node->type, CMD);
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->next_sib_node->next_sib_node->child_node->child_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->next_sib_node->next_sib_node->child_node->child_node->value, "echo");
	ASSERT_EQ(tree->child_node->next_sib_node->next_sib_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->type, TERMINAL);
	ASSERT_STREQ(tree->child_node->next_sib_node->next_sib_node->next_sib_node->next_sib_node->child_node->child_node->next_sib_node->value, "bye now $  C.UTF-8");
}


