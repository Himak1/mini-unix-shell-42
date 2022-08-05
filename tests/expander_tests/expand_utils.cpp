/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 14:08:38 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/04 14:11:27 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
#include "expander.h"
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
    printf("%d\n", expected);
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
    char *input = "hello $HOME";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    expanded = expand_input(input, env_var_list, exp_len);
    ASSERT_STREQ("hello /root", expanded);
}

TEST(expand_input, basic_test2)
{
    char **envp = create_envp();
    char *input = "hello $HI";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    expanded = expand_input(input, env_var_list, exp_len);
    ASSERT_STREQ("hello ", expanded);
}

TEST(expand_input, basic_test3)
{
    char **envp = create_envp();
    char *input = "hello $HOME and $PWD";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    expanded = expand_input(input, env_var_list, exp_len);
    ASSERT_STREQ("hello /root and /pwd/desktop/minishell", expanded);
}

TEST(expand_input, basic_test4)
{
    char **envp = create_envp();
    char *input = "hello $HI and $PWD";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    expanded = expand_input(input, env_var_list, exp_len);
    ASSERT_STREQ("hello  and /pwd/desktop/minishell", expanded);
}

TEST(expand_input, basic_test5)
{
    char **envp = create_envp();
    char *input = "hello $PWD and $HI";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    expanded = expand_input(input, env_var_list, exp_len);
    ASSERT_STREQ("hello /pwd/desktop/minishell and ", expanded);
}

TEST(expand_input, basic_test6)
{
    char **envp = create_envp();
    char *input = "hello $PWD and hi to $HI $";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;
    
    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    expanded = expand_input(input, env_var_list, exp_len);
    ASSERT_STREQ("hello /pwd/desktop/minishell and hi to  $", expanded);
}

TEST(expand_input, basic_test7)
{
    char **envp = create_envp();
    char *input = "hello PWD";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;
    
    if (!env_var)
        ASSERT_STREQ("hello PWD", input);
    else
    {
        create_env_var_list(&env_var_list, env_var);
        check_env_var(&env_var_list, envp);
        exp_len = get_exp_len(env_var_list, len_input);
        expanded = expand_input(input, env_var_list, exp_len);
        ASSERT_STREQ("hello PWD", expanded);
    }
}

TEST(expand_input, basic_test8)
{
    char **envp = create_envp();
    char *input = "I am currently in $PWD";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;

    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    expanded = expand_input(input, env_var_list, exp_len);
    ASSERT_STREQ("I am currently in /pwd/desktop/minishell", expanded);
}

TEST(expand_input, basic_test9)
{
    char **envp = create_envp();
    char *input = "I am currently in /current/dir/is$PWD";
    char **env_var = get_env_var(input);
    int len_input = ft_strlen(input);
    t_env_var *env_var_list = NULL;
    int exp_len;
    char *expanded;

    create_env_var_list(&env_var_list, env_var);
    check_env_var(&env_var_list, envp);
    exp_len = get_exp_len(env_var_list, len_input);
    expanded = expand_input(input, env_var_list, exp_len);
    ASSERT_STREQ("I am currently in /current/dir/is/pwd/desktop/minishell", expanded);
}