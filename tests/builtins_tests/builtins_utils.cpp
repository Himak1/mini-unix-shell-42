/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 10:41:42 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/14 15:53:37 by tvan-der      ########   odam.nl         */
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

TEST(extract_args, basic_test1)
{    
    char input[] = "echo hello world";

    t_token *lst;
    t_ast   *tree;
    char **envp = create_envp();
    char **args;

    lst = NULL;
    ft_lexer(&lst, input);
    tree = parse_tokens(lst);
    expand_tree(tree, envp);
    tree = tree->child_node->child_node;
    while (tree->type != CMD)
        tree->next_sib_node;
    tree = tree->child_node;
    args = extract_args(tree);
    
    ASSERT_STREQ(args[0], "echo");
    ASSERT_STREQ(args[1], "hello");
    ASSERT_STREQ(args[2], "world");
    ASSERT_EQ(args[3], nullptr);
}

TEST(extract_args, basic_test2)
{    
    char input[] = "echo hello $HOME";

    t_token *lst;
    t_ast   *tree;
    char **envp = create_envp();
    char **args;

    lst = NULL;
    ft_lexer(&lst, input);
    tree = parse_tokens(lst);
    expand_tree(tree, envp);
    tree = tree->child_node->child_node;
    while (tree->type != CMD)
        tree->next_sib_node;
    tree = tree->child_node;
    args = extract_args(tree);
    
    ASSERT_STREQ(args[0], "echo");
    ASSERT_STREQ(args[1], "hello");
    ASSERT_STREQ(args[2], "/root");
    ASSERT_EQ(args[3], nullptr);
}

TEST(extract_var_value, basic_test1)
{
    char *variable = "HOME=root";
    char *val = extract_var_value(variable);
    
    ASSERT_STREQ(val, "root");
}

TEST(add_var_to_env_list, basic_test1)
{
    char **arr = (char **)malloc(sizeof(char *) * 3);
    arr[0] = strdup("hello");
    arr[1] = strdup("world");
    arr[2] = NULL;
    
    char **new_arr = add_var_to_env_list("bye", arr);
    ASSERT_STREQ(new_arr[0], "hello");
    ASSERT_STREQ(new_arr[1], "world");
    ASSERT_STREQ(new_arr[2], "bye");
    ASSERT_EQ(new_arr[3], nullptr);
}

TEST(add_var_to_env_list, basic_test2)
{
    char *var = ft_strdup("world");
    char **var_list = (char **)malloc(sizeof(char *) * 2);
    var_list[0] = ft_strdup("hello");
    var_list[1] = NULL;
    
    var_list = add_var_to_env_list(var, var_list);
    ASSERT_STREQ(var_list[1], "world");
}

TEST(add_var_to_env_list, basic_test3)
{
    char **envp = create_envp();
    char *new_var = ft_strdup("hello");
    char **new_envp = add_var_to_env_list(new_var, envp);
    print_envp(new_envp);
    ASSERT_STREQ(new_envp[11], "hello");
}