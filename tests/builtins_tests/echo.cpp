/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 14:08:50 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/15 17:07:35 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "utils.h"
#include "builtins.h"
}

TEST(check_n, basic_test1)
{
    char *test = "hello";

    int i = check_n(test);
    ASSERT_EQ(0, i);
}

TEST(check_n, basic_test2)
{
    char *test = "-n";

    int i = check_n(test);
    ASSERT_EQ(1, i);
}

TEST(check_n, basic_test3)
{
    char *test = "-nnnn";

    int i = check_n(test);
    ASSERT_EQ(1, i);
}

TEST(check_n, basic_test4)
{
    char *test = "-n -n";

    int i = check_n(test);
    ASSERT_EQ(1, i);
}

TEST(get_index_arg, basic_test1)
{
    char **arg = (char **)malloc(sizeof(char *) * 4);
    arg[0] = ft_strdup("echo");
    arg[1] = ft_strdup("hello");
    arg[2] = ft_strdup("world");
    arg[3] = NULL;

    int i = get_index_arg(arg);
    ASSERT_EQ(1, i);
}

TEST(get_index_arg, basic_test2)
{
    char **arg = (char **)malloc(sizeof(char *) * 4);
    arg[0] = ft_strdup("echo");
    arg[1] = ft_strdup("-n");
    arg[2] = ft_strdup("world");
    arg[3] = NULL;

    int i = get_index_arg(arg);
    ASSERT_EQ(2, i);
}

TEST(get_index_arg, basic_test3)
{
    char **arg = (char **)malloc(sizeof(char *) * 5);
    arg[0] = ft_strdup("echo");
    arg[1] = ft_strdup("-nnnn");
    arg[2] = ft_strdup("-n");
    arg[3] = ft_strdup("hello");
    arg[4] = NULL;

    int i = get_index_arg(arg);
    ASSERT_EQ(3, i);
}