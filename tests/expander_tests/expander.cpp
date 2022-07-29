/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 15:18:48 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/29 16:54:00 by Tessa         ########   odam.nl         */
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

TEST(save_exp_val, test_found)
{
    char *alias = "NAME";
    char *full_var = "NAME=tessa";
    char *val;

    val = save_exp_val(full_var, alias);
    ASSERT_STREQ("tessa", val);
}

TEST(save_exp_val, test_not_found)
{
    char *alias = "NAME";
    char *full_var = "NAME_=tessa";
    char *val;

    val = save_exp_val(full_var, alias);
    ASSERT_STREQ(NULL, val);
}

TEST(find_exp_var, test_found)
{
    char *env_var = "$HOME";
    char **envp = create_envp();
    char *exp_val = find_exp_var(env_var, envp);
    
    ASSERT_STREQ("/root", exp_val);
}

TEST(find_exp_var, test_one_dollar_sign)
{
    char *env_var = "$";
    char **envp = create_envp();
    char *exp_val = find_exp_var(env_var, envp);
    
    ASSERT_STREQ("$", exp_val);
}

TEST(find_exp_var, test_not_found)
{
    char *env_var = "$USER";
    char **envp = create_envp();
    char *exp_val = find_exp_var(env_var, envp);
    
    ASSERT_STREQ(NULL, exp_val);
}

TEST(check_env_var, test_found1)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $HOME and $PWD");
    t_env_var *env_var_list = NULL;
    
    create_env_var_list(&env_var_list, env_var);
    ASSERT_STREQ("$HOME", env_var_list->env_value);

    check_env_var(&env_var_list, envp);
    ASSERT_STREQ("/root", env_var_list->exp_env_value);
    ASSERT_EQ(ft_strlen("/root"), env_var_list->len_exp_env);
    ASSERT_STREQ("/pwd/desktop/minishell", env_var_list->next->exp_env_value);
    ASSERT_EQ(ft_strlen("/pwd/desktop/minishell"), env_var_list->next->len_exp_env);
}

TEST(check_env_var, test_found2)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $HOME and $");
    t_env_var *env_var_list = NULL;
    
    create_env_var_list(&env_var_list, env_var);
    ASSERT_STREQ("$HOME", env_var_list->env_value);

    check_env_var(&env_var_list, envp);
    ASSERT_STREQ("/root", env_var_list->exp_env_value);
    ASSERT_EQ(ft_strlen("/root"), env_var_list->len_exp_env);
    ASSERT_STREQ("$", env_var_list->next->exp_env_value);
    ASSERT_EQ(ft_strlen("$"), env_var_list->next->len_exp_env);
    ASSERT_EQ(NULL, env_var_list->next->next);
}

TEST(check_env_var, test_not_found3)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $HI");
    t_env_var *env_var_list = NULL;
    
    create_env_var_list(&env_var_list, env_var);
    ASSERT_STREQ("$HI", env_var_list->env_value);

    check_env_var(&env_var_list, envp);
    ASSERT_STREQ(NULL, env_var_list->exp_env_value);
    ASSERT_EQ(0, env_var_list->len_exp_env);
}

TEST(check_env_var, test_found_and_not_found1)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $HOME and $HI");
    t_env_var *env_var_list = NULL;
    
    create_env_var_list(&env_var_list, env_var);

    check_env_var(&env_var_list, envp);
    ASSERT_STREQ("/root", env_var_list->exp_env_value);
    ASSERT_EQ(ft_strlen("/root"), env_var_list->len_exp_env);
    ASSERT_STREQ(NULL, env_var_list->next->exp_env_value);
    ASSERT_EQ(0, env_var_list->next->len_exp_env);
}

TEST(check_env_var, test_found_and_not_found2)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $HI and $HOME");
    t_env_var *env_var_list = NULL;
    
    create_env_var_list(&env_var_list, env_var);

    check_env_var(&env_var_list, envp);
    ASSERT_STREQ(NULL, env_var_list->exp_env_value);
    ASSERT_EQ(0, env_var_list->len_exp_env);
    ASSERT_STREQ("/root", env_var_list->next->exp_env_value);
    ASSERT_EQ(ft_strlen("/root"), env_var_list->next->len_exp_env);
}

TEST(get_exp_len, basic_test1)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $CHARSET");
    int len_input = ft_strlen("hello $CHARSET");
    t_env_var *env_var_list = NULL;
    int exp_len;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    
    int expected = len_input + (ft_strlen("UTF-8") - ft_strlen("$CHARSET"));
    ASSERT_EQ(expected, exp_len);
}

TEST(get_exp_len, basic_test2)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $LANG");
    int len_input = ft_strlen("hello $LANG");
    t_env_var *env_var_list = NULL;
    int exp_len;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    
    int expansion = ft_strlen("C.UTF-8") - ft_strlen("$NAME");
    int expected = len_input + expansion;
    ASSERT_EQ(expected, exp_len);
}

TEST(get_exp_len, basic_test3)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $LANG and $");
    int len_input = ft_strlen("hello $LANG and $");
    t_env_var *env_var_list = NULL;
    int exp_len;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    
    int expansion = (ft_strlen("C.UTF-8") + ft_strlen("$")) - (ft_strlen("$LANG") + ft_strlen("$"));
    int expected = len_input + expansion;
    ASSERT_EQ(expected, exp_len);
}

TEST(get_exp_len, basic_test4)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $hello");
    int len_input = ft_strlen("hello $hello");
    t_env_var *env_var_list = NULL;
    int exp_len;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    
    int expansion = 0 - ft_strlen("$hello");
    int expected = len_input + expansion;
    ASSERT_EQ(expected, exp_len);
}

TEST(get_exp_len, basic_test5)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $hello and $");
    int len_input = ft_strlen("hello $hello and $");
    t_env_var *env_var_list = NULL;
    int exp_len;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    
    int expansion = (0 + ft_strlen("$")) - (ft_strlen("$hello") + ft_strlen("$"));
    int expected = len_input + expansion;
    ASSERT_EQ(expected, exp_len);
}

TEST(expand_input, basic_test1)
{
    char **envp = create_envp();
    char **env_var = get_env_var("hello $hello and $");
    int len_input = ft_strlen("hello $hello and $");
    t_env_var *env_var_list = NULL;
    int exp_len;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    
    int expansion = (0 + ft_strlen("$")) - (ft_strlen("$hello") + ft_strlen("$"));
    int expected = len_input + expansion;
    ASSERT_EQ(expected, exp_len);
}