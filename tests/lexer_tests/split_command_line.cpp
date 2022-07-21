/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_command_line.cpp                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 15:07:25 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/20 12:35:48 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
#include "utils.h"
}

TEST(count_tokens, basic_test)
{
    char const *s = "hello world";

    ASSERT_EQ(2, count_tokens(s));
}

TEST(count_tokens, basic_test1)
{
    char const *s = "echo";

    ASSERT_EQ(1, count_tokens(s));
}

TEST(count_tokens, with_quotes_test1)
{
    char const *s = "echo \"hello world\"";

    ASSERT_EQ(2, count_tokens(s));
}

TEST(count_tokens, with_quotes_test2)
{
    char const *s = "echo \"hello world hi\"";

    ASSERT_EQ(2, count_tokens(s));
}

TEST(count_tokens, with_quotes_test3)
{
    char const *s = "echo \"hello world hi\" hello";

    ASSERT_EQ(3, count_tokens(s));
}

TEST(count_tokens, with_quotes_test4)
{
    char const *s = "echo he\"lo hel\"lo";

    ASSERT_EQ(2, count_tokens(s));
}

TEST(count_tokens, empty_string)
{
    char const *s = "";

    ASSERT_EQ(0, count_tokens(s));
}

TEST(count_tokens, nullptr)
{
    char const *s = NULL;

    ASSERT_EQ(0, count_tokens(s));
}

TEST(count_tokens, single_quotes1)
{
    char const *s = "echo hel\'lo hel\'lo";
    ASSERT_EQ(2, count_tokens(s));
}

TEST(count_tokens, single_and_double1)
{
    char const *s = "echo \"hello \'hi\'\"";
    ASSERT_EQ(2, count_tokens(s));
}

TEST(count_tokens, single_and_double2)
{
    char const *s = "echo \'hello \"hi\" bye\'";
    ASSERT_EQ(2, count_tokens(s));
}

TEST(split_command_line, basic_test)
{
    char *s = "echo hello";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("hello", test[1]);
    ASSERT_STREQ(NULL, test[2]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_dquote_test1)
{
    char *s = "echo \"hello hi\"";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("\"hello hi\"", test[1]);
    ASSERT_STREQ(NULL, test[2]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_dquote_test2)
{
    char *s = "echo \"hello hi \"";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("\"hello hi \"", test[1]);
    ASSERT_STREQ(NULL, test[2]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_dquote_test3)
{
    char *s = "echo \"hello hi\" hello";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("\"hello hi\"", test[1]);
    ASSERT_STREQ("hello", test[2]);
    ASSERT_STREQ(NULL, test[3]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_dquote_test4)
{
    char *s = "echo \"hello hi\"             hello    \"bye\"";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("\"hello hi\"", test[1]);
    ASSERT_STREQ("hello", test[2]);
    ASSERT_STREQ("\"bye\"", test[3]);
    ASSERT_STREQ(NULL, test[4]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_dquote_test5)
{
    char *s = "echo he\"lo hel\"lo";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("he\"lo hel\"lo", test[1]);
    ASSERT_STREQ(NULL, test[2]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_dquote_and_squote1)
{
    char *s = "echo \"hello \'hi\' hello\" hi";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("\"hello \'hi\' hello\"", test[1]);
    ASSERT_STREQ("hi", test[2]);
    ASSERT_STREQ(NULL, test[3]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_dquote_and_squote2)
{
    char *s = "echo \'hello \"hi\" hello\' hi";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("\'hello \"hi\" hello\'", test[1]);
    ASSERT_STREQ("hi", test[2]);
    ASSERT_STREQ(NULL, test[3]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_squote_test1)
{
    char *s = "echo \'hello hi\'";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("\'hello hi\'", test[1]);
    ASSERT_STREQ(NULL, test[2]);
    ft_free_2d_array(test);
}

TEST(split_command_line, with_squote_test2)
{
    char *s = "echo he\'lo hel\'lo";
    char **test;
    
    test = split_command_line(s);
    ASSERT_STREQ("echo", test[0]);
    ASSERT_STREQ("he\'lo hel\'lo", test[1]);
    ASSERT_STREQ(NULL, test[2]);
    ft_free_2d_array(test);
}