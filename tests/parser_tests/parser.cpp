/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 11:31:33 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/16 14:49:29 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
}

// ---- input templates ---- //

t_token	*parser_input(void)
{
	t_token	*t;

	t = lst_new(RDR_IN, ft_strdup("<"));
	lst_add_bk(&t, lst_new(WORD, ft_strdup("infile")));
	lst_add_bk(&t, lst_new(WORD, ft_strdup("echo")));
	lst_add_bk(&t, lst_new(WORD, ft_strdup("hello")));
	lst_add_bk(&t, lst_new(PIPE, ft_strdup("|")));
	lst_add_bk(&t, lst_new(WORD, ft_strdup("echo")));
	lst_add_bk(&t, lst_new(WORD, ft_strdup("world")));
	return (t);
}

t_token	*create_list(int *types, char const **terms)
{
	int		i;
	t_token	*lst;

	i = 1;
	lst = lst_new(types[0], (char*)terms[0]);
	while (terms[i])
	{
		lst_add_bk(&lst, lst_new(types[i], ft_strdup(terms[i])));
		i++;
	}
	return (lst);
}

// ---- TESTS ---- //
TEST(exec_block, basic)
{
	int			types[] = {RDR_IN, WORD, WORD, WORD};
	char const	*terms[] = {"<", "infile", "echo", "hello", NULL};
	t_token *input = create_list(types, terms);
	t_token	*head = input;

	t_ast	*output = exec_block(&head);
	EXPECT_EQ(output->type, EXEC_BLOCK);
	free_ast(output);
	free(output);
}

TEST(exec_block, only_rd)
{
	t_token	*t1 = lst_new(RDR_IN, ft_strdup("<"));
	t_token	*t2 = lst_new(WORD, ft_strdup("file"));
	t_token	*head = t1;
	lst_add_bk(&t1, t2);

	t_ast	*output = exec_block(&head);
	EXPECT_EQ(output->type, EXEC_BLOCK);
	EXPECT_EQ(output->child_node->type, RDS);
	free_ast(output);
	free(output);
}

TEST(parse_pipe, basic)
{
	t_token	*t1 = lst_new(PIPE, ft_strdup("|"));
	t_token	*head = t1;

	t_ast	*output = parse_pipe(&head);
	EXPECT_EQ(output->type, TERMINAL);
	EXPECT_STREQ(output->value, "|");
	free(output);
}

TEST(parse_token, basic)
{
	int			types[] = {RDR_IN, WORD, WORD, WORD};
	char const	*terms[] = {"<", "infile", "echo", "hello", NULL};
	t_token *input = create_list(types, terms);

	t_ast	*tree;
	tree = parse_tokens(input);
	ASSERT_TRUE(tree->child_node != nullptr);
	EXPECT_EQ(tree->child_node->next_sib_node, nullptr);
	EXPECT_STREQ(tree->child_node->child_node->child_node->child_node->value, "<");
	free_ast(tree);
	free(tree);
}

TEST(parse_token, 2_commands)
{
	t_token	*list = parser_input();

	t_ast	*tree = parse_tokens(list);
	ASSERT_TRUE(tree != nullptr);
}