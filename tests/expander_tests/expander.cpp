/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 15:18:48 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/18 16:24:17 by tvan-der      ########   odam.nl         */
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

TEST(expand_dollar_sign, basic_test1)
{
    char **envp = create_envp();
    char *input = ft_strdup("\"I am currently in $PWD\"");
    char *expanded = expand_dollar_sign(input, envp);

    ASSERT_STREQ("\"I am currently in /pwd/desktop/minishell\"", expanded);
}

TEST(expand_dollar_sign, basic_test2)
{
    char **envp = create_envp();
    char *input = ft_strdup("This is not a var $HELLO but this is $LANG");
    char *expanded = expand_dollar_sign(input, envp);

    ASSERT_STREQ("This is not a var  but this is C.UTF-8", expanded);
}

TEST(expand_dollar_sign, basic_test3)
{
    char **envp = create_envp();
    char *input = ft_strdup("I am $ currently $ in $PWDnot this $hi");
    char *expanded = expand_dollar_sign(input, envp);

    ASSERT_STREQ("I am $ currently $ in  this ", expanded);
}

TEST(expand_dollar_sign, basic_test4)
{
    char **envp = create_envp();
    char *input = ft_strdup("$hello");
    char *expanded = expand_dollar_sign(input, envp);

    ASSERT_STREQ("", expanded);
}

TEST(expander, only_env1)
{
    char *input = ft_strdup("$PWD");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("/pwd/desktop/minishell", input);
}

TEST(expander, only_env2)
{
    char *input = ft_strdup("$PWd");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("", input);
}

TEST(expander, basic_test1)
{
    char *input = ft_strdup("\"hello i am currently in $PWD\"");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("hello i am currently in /pwd/desktop/minishell", input);
}

TEST(expander, basic_test2)
{
    char *input = ft_strdup("\'hello i am currently in $PWD\'");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("hello i am currently in $PWD", input);
}

TEST(expander, basic_test3)
{
    char *input = ft_strdup("\"hello i am currently in $PWD        $      not an var $HELLO bye\"");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("hello i am currently in /pwd/desktop/minishell        $      not an var  bye", input);
}

TEST(expander, basic_test4)
{
    char *input = ft_strdup("\"hello \'$PWD\' bye now\"");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("hello \'/pwd/desktop/minishell\' bye now", input);
}

TEST(expander, basic_test5)
{
    char *input = ft_strdup("echo he\"ll\"o");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("echo hello", input);
}

TEST(expander, basic_test6)
{
    char *input = ft_strdup("e\"ch\"o \'he\"ll\"o\'");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("echo he\"ll\"o", input);
}

TEST(expander, basic_test7)
{
    char *input = ft_strdup("echo he\"l\'l\'\"o");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("echo hel\'l\'o", input);
}

TEST(expander, basic_test8)
{
    char *input = ft_strdup("echo current dir is\" $PWD\"");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("echo current dir is /pwd/desktop/minishell", input);
}

TEST(expander, basic_test9)
{
    char *input = ft_strdup("echo $_");
    char **envp = create_envp();
    expander(&input, envp);
    
    ASSERT_STREQ("echo /usr/bin/env", input);
}