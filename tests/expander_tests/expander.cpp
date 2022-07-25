/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 15:18:48 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/25 15:39:18 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
#include "expander.h"
}

TEST(create_envp, basic_test)
{
    char **envp = NULL;

    envp = create_envp();
    ASSERT_STREQ(envp[0], "CHARSET=UTF-8");
    ASSERT_STREQ(envp[1], "HOSTNAME=a4d647f5f42a");
    ASSERT_STREQ(envp[2], "PWD=/pwd/desktop/minishell");
    ASSERT_STREQ(envp[3], "HOME=/root");
    ASSERT_STREQ(envp[4], "LANG=C.UTF-8");
    ASSERT_STREQ(envp[5], "TERM=xterm");
    ASSERT_STREQ(envp[6], "SHLVL=2");
    ASSERT_STREQ(envp[7], "LC_COLLATE=C");
    ASSERT_STREQ(envp[8], "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
    ASSERT_STREQ(envp[9], "OLDPWD=/pwd/desktop/minishell/build");
    ASSERT_STREQ(envp[10], "_=/usr/bin/env");
}

TEST(remove_quotes, basic_test_dquote)
{
    char *test = strdup("\"hello\"");
    char *new_str = remove_quotes(test, test[0]);
    
    ASSERT_STREQ(new_str, "hello");
}

TEST(remove_quotes, basic_test_squote)
{
    char *test = strdup("\'hello\'");
    char *new_str = remove_quotes(test, test[0]);
    
    ASSERT_STREQ(new_str, "hello");
}

TEST(remove_quotes, basic_test_combi1)
{
    char *test = strdup("\"hel\'l\'o\"");
    char *new_str = remove_quotes(test, test[0]);
    
    ASSERT_STREQ(new_str, "hel\'l\'o");
}

TEST(remove_quotes, basic_test_combi2)
{
    char *test = strdup("\'hell\"o\"");
    char *new_str = remove_quotes(test, test[0]);
    
    ASSERT_STREQ(new_str, "hell\"o\"");
}

TEST(count_dollar_sign, basic_test1)
{
    char *str = "hello $HOME";
    int count = count_dollar_sign(str);
    
    ASSERT_EQ(count, 1);
}

TEST(count_dollar_sign, basic_test2)
{
    char *str = "hello$HOME";
    int count = count_dollar_sign(str);
    
    ASSERT_EQ(count, 1);
}

TEST(count_dollar_sign, basic_test3)
{
    char *str = "hello $HOME$hi";
    int count = count_dollar_sign(str);
    
    ASSERT_EQ(count, 2);
}

TEST(count_dollar_sign, zero)
{
    char *str = "hello HOMEhi";
    int count = count_dollar_sign(str);
    
    ASSERT_EQ(count, 0);
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

TEST(expand_dollar_sign, basic_test1)
{
    char *test = "hi $hello";
    char **env_var = expand_dollar_sign(test);

    ASSERT_STREQ(env_var[0], "hello");
    ASSERT_EQ(env_var[1], NULL);
}

TEST(expand_dollar_sign, basic_test2)
{
    char *test = "hi $hello$hi";
    char **env_var = expand_dollar_sign(test);

    ASSERT_STREQ(env_var[0], "hello");
    ASSERT_STREQ(env_var[1], "hi");
    ASSERT_EQ(env_var[2], NULL);
}
