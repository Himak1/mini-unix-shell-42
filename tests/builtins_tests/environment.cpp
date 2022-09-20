/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 16:06:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/20 14:29:25 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "utils.h"
#include "parser.h"
#include "lexer.h"
#include "builtins.h"
#include "expander.h"
}


TEST(compare_key, basic_test1)
{
    char *full_var = NULL;
    char *key = "var1";
    
    int i = compare_key(full_var, key);
    ASSERT_EQ(i, 0);
}

TEST(compare_key, basic_test2)
{
    char *full_var = "var1";
    char *key = "var1=hello";
    
    int i = compare_key(full_var, key);
    ASSERT_EQ(i, 1);
}

TEST(compare_key, basic_test3)
{
    char *full_var = "var1=hello";
    char *key = "var1";
    
    int i = compare_key(full_var, key);
    ASSERT_EQ(i, 1);
}

TEST(compare_key, basic_test4)
{
    char *full_var = "var2=hello";
    char *key = "var1";
    
    int i = compare_key(full_var, key);
    ASSERT_EQ(i, 0);
}

TEST(compare_key, basic_test5)
{
    char *full_var = "var1";
    char *key = "var1";
    
    int i = compare_key(full_var, key);
    ASSERT_EQ(i, 1);
}

TEST(compare_key, basic_test6)
{
    char *full_var = "var";
    char *key = "var1";
    
    int i = compare_key(full_var, key);
    ASSERT_EQ(i, 0);
}

TEST(compare_key, basic_test7)
{
    char *full_var = "var1";
    char *key = "var";
    
    int i = compare_key(full_var, key);
    ASSERT_EQ(i, 0);
}