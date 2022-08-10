/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var_utils.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 14:10:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/10 13:30:03 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
#include "expander.h"
}

TEST(get_env_var_len, basic_test1)
{
    char *test = "hello hi";
    int count = get_env_var_len(test);
    
    ASSERT_EQ(count, 5);
}

TEST(get_env_var_len, basic_test2)
{
    char *test = "hello$hi";
    int count = get_env_var_len(test);
    
    ASSERT_EQ(count, 5);
}

TEST(get_env_var_len, basic_test3)
{
    char *test = "PWD\"";
    int count = get_env_var_len(test);
    
    ASSERT_EQ(count, 3);
}

TEST(get_env_var, basic_test1)
{
    char *test = "hi $hello";
    char **env_var = get_env_var(test);

    ASSERT_STREQ(env_var[0], "$hello");
    ASSERT_STREQ(env_var[1], NULL);
}

TEST(get_env_var, basic_test2)
{
    char *test = "hi $hello$hi";
    char **env_var = get_env_var(test);

    ASSERT_STREQ(env_var[0], "$hello");
    ASSERT_STREQ(env_var[1], "$hi");
    ASSERT_STREQ(env_var[2], NULL);
}

TEST(get_env_var, basic_test3)
{
    char *test = "hi $hello $";
    char **env_var = get_env_var(test);

    ASSERT_STREQ(env_var[0], "$hello");
    ASSERT_STREQ(env_var[1], "$");
    ASSERT_STREQ(env_var[2], NULL);
}

TEST(get_env_var, basic_test4)
{
    char *test = "hello $HOME and $PWD";
    char **env_var = get_env_var(test);

    ASSERT_STREQ(env_var[0], "$HOME");
    ASSERT_STREQ(env_var[1], "$PWD");
    ASSERT_STREQ(env_var[2], NULL);
}

TEST(get_env_var, basic_test5)
{
    char *test = "hello PWD";
    char **env_var = get_env_var(test);

    ASSERT_EQ(env_var, nullptr);
}

TEST(create_env_var_list, basic_test1)
{
    t_env_var *test = NULL;
    char **env_var = get_env_var("hello $NAME bye hello $now$");
    create_env_var_list(&test, env_var);
    ASSERT_STREQ("$NAME", test->env_value);
    ASSERT_EQ(ft_strlen("$NAME"), test->len_env);
    ASSERT_STREQ("$now", test->next->env_value);
    ASSERT_EQ(ft_strlen("$now"), test->next->len_env);
    ASSERT_STREQ("$", test->next->next->env_value);
    ASSERT_EQ(ft_strlen("$"), test->next->next->len_env);
    ASSERT_EQ(NULL, test->next->next->next);
}

TEST(create_env_var_list, basic_test2)
{
    t_env_var *test = NULL;
    char **env_var = get_env_var("hello $HOME and $PWD");
    create_env_var_list(&test, env_var);
    ASSERT_STREQ("$HOME", test->env_value);
    ASSERT_EQ(ft_strlen("$HOME"), test->len_env);
    ASSERT_STREQ("$PWD", test->next->env_value);
    ASSERT_EQ(ft_strlen("$PWD"), test->next->len_env);
    ASSERT_EQ(NULL, test->next->next);
}
