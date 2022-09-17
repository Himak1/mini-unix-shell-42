/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 13:16:48 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/16 13:40:04 by tvan-der      ########   odam.nl         */
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

TEST(pop_var_from_env, basic_test1)
{
    char **test = (char **)malloc(sizeof(char *) * 3);
    test[0] = ft_strdup("hi");
    test[1] = ft_strdup("hello");
    test[2] = NULL;
    int index = ft_get_index_2d(test, "hello");
    pop_var_from_env(index, &test);
    int i = 0;
    while (test[i])
    {
        printf("%s\n", test[i]);
        i++;
    }
    // ASSERT_STREQ(test[1], nullptr);
    ASSERT_EQ(i, 2);
}