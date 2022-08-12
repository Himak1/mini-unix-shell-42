/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 14:30:15 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/11 15:25:59 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
#include "expander.h"
}

TEST(len_filtered_quotes, basic_test1)
{
    char *val = "he\"ll\"o";
    int count = len_filtered_quotes(val);
    
    ASSERT_EQ(count, 5);
}

TEST(len_filtered_quotes, basic_test2)
{
    char *val = "he\'ll\'o";
    int count = len_filtered_quotes(val);
    
    ASSERT_EQ(count, 5);
}

TEST(len_filtered_quotes, basic_test3)
{
    char *val = "\"he\'ll\'o\"";
    int count = len_filtered_quotes(val);
    
    ASSERT_EQ(count, 7);
}

TEST(len_filtered_quotes, basic_test4)
{
    char *val = "\'he\"ll\"o\'";
    int count = len_filtered_quotes(val);
    
    ASSERT_EQ(count, 7);
}

TEST(len_filtered_quotes, basic_test5)
{
    char *val = "\'he\"l\'ll\'l\"o\'";
    int count = len_filtered_quotes(val);
    
    ASSERT_EQ(count, 9);
}

TEST(len_filtered_quotes, basic_test6)
{
    char *val = "\"lol\"\"lols\"";
    int count = len_filtered_quotes(val);
    
    ASSERT_EQ(count, 7);
}

TEST(remove_quotes, basic_test_dquote)
{
    char *test = strdup("\"hello\"");
    char *new_str = remove_quotes(test);
    
    ASSERT_STREQ(new_str, "hello");
}

TEST(remove_quotes, basic_test_squote)
{
    char *test = strdup("\'hello\'");
    char *new_str = remove_quotes(test);
    
    ASSERT_STREQ(new_str, "hello");
}

TEST(remove_quotes, basic_test_inbetween1)
{
    char *test = strdup("he\"ll\"o");
    char *new_str = remove_quotes(test);
    
    ASSERT_STREQ(new_str, "hello");
}

TEST(remove_quotes, basic_test_inbetween2)
{
    char *test = strdup("he\'ll\'o");
    char *new_str = remove_quotes(test);
    
    ASSERT_STREQ(new_str, "hello");
}

TEST(remove_quotes, basic_test_combi1)
{
    char *test = strdup("\"hell\'o\'\"");
    char *new_str = remove_quotes(test);
    
    ASSERT_STREQ(new_str, "hell\'o\'");
}

TEST(remove_quotes, basic_test_combi2)
{
    char *test = strdup("\'hell\"o\"\'");
    char *new_str = remove_quotes(test);
    
    ASSERT_STREQ(new_str, "hell\"o\"");
}
