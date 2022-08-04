/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lexer.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 12:08:47 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/20 12:48:02 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
#include "utils.h"
}

TEST(get_type, word)
{
	ASSERT_EQ(get_type("cat"), WORD);
	ASSERT_EQ(get_type("$,"), WORD);
	ASSERT_EQ(get_type("$."), WORD);
	ASSERT_EQ(get_type("$"), WORD);
	ASSERT_EQ(get_type("\'hi\'"), WORD);
	ASSERT_EQ(get_type("he\'lo hel\'lo"), WORD);
	ASSERT_EQ(get_type("he\"lo hel\"lo"), WORD);
	ASSERT_EQ(get_type("$s"), WORD);
	ASSERT_EQ(get_type("$aDa"), WORD);
	ASSERT_EQ(get_type("$PATH"), WORD);
	ASSERT_EQ(get_type("\"hello\""), WORD);
	ASSERT_EQ(get_type("\"    hello\""), WORD);
	ASSERT_EQ(get_type("$?"), WORD);
}

TEST(get_type, rdr_in)
{
	ASSERT_EQ(get_type("<"), RDR_IN);
}

TEST(get_type, rdr_out)
{
	ASSERT_EQ(get_type(">"), RDR_OUT);
}

TEST(get_type, rdr_dlm_in)
{
	ASSERT_EQ(get_type("<<"), RDR_DLM_IN);
}

TEST(get_type, rdr_dlm_out)
{
	ASSERT_EQ(get_type(">>"), RDR_APND_OUT);
}

TEST(get_type, pipe)
{
	ASSERT_EQ(get_type("|"), PIPE);
}

TEST(create_tokenlist, simple_command1)
{
	t_token *test = NULL;
    char *test_command = "echo hello world";
	char **split_command = split_command_line(test_command);
    
	create_tokenlist(&test, split_command);
    ASSERT_STREQ("echo", test->value);
    ASSERT_STREQ("hello", test->next->value);
	ASSERT_STREQ("world", test->next->next->value);
    ft_free_2d_array(split_command);
    ft_lstfree(test);
}

TEST(create_tokenlist, simple_command2)
{
	t_token *test = NULL;
    char *test_command = "echo > file | echo $PATH";
	char **split_command = split_command_line(test_command);
    
	create_tokenlist(&test, split_command);
    ASSERT_STREQ("echo", test->value);
	ASSERT_STREQ(">", test->next->value);
	ASSERT_STREQ("file", test->next->next->value);
	ASSERT_STREQ("|", test->next->next->next->value);
	ASSERT_STREQ("echo", test->next->next->next->next->value);
	ASSERT_STREQ("$PATH", test->next->next->next->next->next->value);
    ft_free_2d_array(split_command);
    ft_lstfree(test);
}

TEST(create_tokenlist, simple_command3)
{
	t_token *test = NULL;
    char *test_command = "     echo hello world";
	char **split_command = split_command_line(test_command);
    
	create_tokenlist(&test, split_command);
    ASSERT_STREQ("echo", test->value);
    ASSERT_STREQ("hello", test->next->value);
	ASSERT_STREQ("world", test->next->next->value);
	ASSERT_EQ(NULL, test->next->next->next);
    ft_free_2d_array(split_command);
    ft_lstfree(test);
}

TEST(create_tokenlist, simple_command4)
{
	t_token *test = NULL;
    char *test_command = "echo \"hello hi\"             hello    \"bye\"";
	char **split_command = split_command_line(test_command);
    
	create_tokenlist(&test, split_command);
    ASSERT_STREQ("echo", test->value);
    ASSERT_STREQ("\"hello hi\"", test->next->value);
	ASSERT_STREQ("hello", test->next->next->value);
	ASSERT_STREQ("\"bye\"", test->next->next->next->value);
	ASSERT_EQ(NULL, test->next->next->next->next);
    ft_free_2d_array(split_command);
    ft_lstfree(test);
}

TEST(create_tokenlist, simple_command5)
{
	t_token *test = NULL;
    char *test_command = "echo \"hello $hi\"";
	char **split_command = split_command_line(test_command);
    
	create_tokenlist(&test, split_command);
	ASSERT_STREQ("echo", test->value);
    ASSERT_STREQ("\"hello $hi\"", test->next->value);
	ASSERT_EQ(NULL, test->next->next);
    ft_free_2d_array(split_command);
    ft_lstfree(test);
}

TEST(ft_lexer, simple_command6)
{
	t_token *test = NULL;
    char *test_command = "echo \"hello \'hello there\' hi\"             \'hello\'    \"bye\"";
    
	ft_lexer(&test, test_command);
    ASSERT_STREQ("echo", test->value);
    ASSERT_STREQ("\"hello \'hello there\' hi\"", test->next->value);
	ASSERT_STREQ("\'hello\'", test->next->next->value);
	ASSERT_STREQ("\"bye\"", test->next->next->next->value);
	ASSERT_EQ(NULL, test->next->next->next->next);
    ft_lstfree(test);
}

TEST(ft_lexer, simple_command7)
{
	t_token *test = NULL;
    char *test_command = "echo he\"lo hel\"lo";
    
	ft_lexer(&test, test_command);
	printf("%s\n", test->value);
    ASSERT_STREQ("echo", test->value);
    ASSERT_STREQ("he\"lo hel\"lo", test->next->value);
	ASSERT_EQ(NULL, test->next->next);
    ft_lstfree(test);
}

TEST(ft_lexer, simple_command8)
{
	t_token *test = NULL;
    char *test_command = "echo he\'lo hel\'lo";
    
	ft_lexer(&test, test_command);
	printf("%s\n", test->value);
    ASSERT_STREQ("echo", test->value);
    ASSERT_STREQ("he\'lo hel\'lo", test->next->value);
	ASSERT_EQ(NULL, test->next->next);
    ft_lstfree(test);
}

