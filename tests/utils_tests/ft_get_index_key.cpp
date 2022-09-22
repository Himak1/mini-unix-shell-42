/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_index_key.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 18:28:58 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/20 19:16:52 by tvan-der      ########   odam.nl         */
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

TEST(ft_get_index_key, basic_test1)
{
    char **test = (char **)malloc(sizeof(char *) * 4);
    test[0] = "var2";
    test[1] = "var1";
    test[2] = "var";
    test[3] = nullptr;
    
    int index = ft_get_index_key(test, "var");
    ASSERT_EQ(index, 2);
}

TEST(ft_get_index_key, basic_test2)
{
    char **test = (char **)malloc(sizeof(char *) * 4);
    test[0] = "var2";
    test[1] = "var1";
    test[2] = "var";
    test[3] = nullptr;
    
    int index = ft_get_index_key(test, "var2");
    ASSERT_EQ(index, 0);
}

TEST(ft_get_index_key, basic_test3)
{
    char **test = (char **)malloc(sizeof(char *) * 4);
    test[0] = "var2";
    test[1] = "var1";
    test[2] = "var";
    test[3] = nullptr;
    
    int index = ft_get_index_key(test, "va");
    ASSERT_EQ(index, -1);
}

