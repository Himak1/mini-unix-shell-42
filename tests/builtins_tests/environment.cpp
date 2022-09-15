/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 16:06:59 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/14 14:55:34 by tvan-der      ########   odam.nl         */
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

// TEST(update_underscore, basic_test1)
// {
//     char input[] = "echo hello world";

// 	t_token *lst;
// 	t_ast   *tree;
// 	char **envp = create_envp();

// 	lst = NULL;
// 	ft_lexer(&lst, input);
// 	tree = parse_tokens(lst);
// 	expand_tree(tree, envp);
//     tree = tree->child_node->child_node;
//     while (tree->type != CMD)
//         tree->next_sib_node;
//     tree = tree->child_node;
    
//     int index = ft_get_index_2d(envp, "_=");
//     ASSERT_STREQ(envp[index], "_=/usr/bin/env");
//     update_underscore(tree, envp);
//     ASSERT_STREQ(envp[index], "_=world");
// }

// TEST(update_underscore, basic_test2)
// {
//     char input[] = "ls -la";

// 	t_token *lst;
// 	t_ast   *tree;
// 	char **envp = create_envp();

// 	lst = NULL;
// 	ft_lexer(&lst, input);
// 	tree = parse_tokens(lst);
// 	expand_tree(tree, envp);
//     tree = tree->child_node->child_node;
//     while (tree->type != CMD)
//         tree->next_sib_node;
//     tree = tree->child_node;
    
//     int index = ft_get_index_2d(envp, "_=");
//     ASSERT_STREQ(envp[index], "_=/usr/bin/env");
//     update_underscore(tree, envp);
//     ASSERT_STREQ(envp[index], "_=-la");
// }

// TEST(update_underscore, env)
// {
//     char input[] = "env";

// 	t_token *lst;
// 	t_ast   *tree;
// 	char **envp = create_envp();

// 	lst = NULL;
// 	ft_lexer(&lst, input);
// 	tree = parse_tokens(lst);
// 	expand_tree(tree, envp);
//     tree = tree->child_node->child_node;
//     while (tree->type != CMD)
//         tree->next_sib_node;
//     tree = tree->child_node;

//     int index = ft_get_index_2d(envp, "_=");
//     ASSERT_STREQ(envp[index], "_=/usr/bin/env");
//     update_underscore(tree, envp);
//     ASSERT_STREQ(envp[index], "_=/usr/bin/env");
// }

// TEST(add_var, basic_test1)
// {
//     char *name = "OLDPWD";
//     char **envp = NULL;
// 	envp = (char **)malloc((11) * sizeof(char *));
// 	envp[0] = ft_strdup("CHARSET=UTF-8");
// 	envp[1] = ft_strdup("ZDOTDIR=njfjsv");
// 	envp[2] = ft_strdup("PWD=/pwd/desktop/minishell");
// 	envp[3] = ft_strdup("HOME=/root");
// 	envp[4] = ft_strdup("LANG=C.UTF-8");
// 	envp[5] = ft_strdup("TERM=xterm");
// 	envp[6] = ft_strdup("SHLVL=2");
// 	envp[7] = ft_strdup("LC_COLLATE=C");
// 	envp[8] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
// 	envp[9] = ft_strdup("_=/usr/bin/env");
// 	envp[10] = NULL;

//     char **updated_envp = add_oldpwd(envp);
//     int index = ft_get_index_2d(updated_envp, "OLDPWD=");
//     print_envp(updated_envp);
//     ASSERT_STREQ(updated_envp[index], "OLDPWD=");
// }

// // TEST(update_old_pwd, basic_test_old_pwd_exists)
// // {
// //     char **envp = create_envp();

// //     update_old_pwd(envp);
    
// // }

// TEST(update_old_pwd, basic_test_old_pwd_not_exists)
// {
//     char **envp = NULL;
// 	envp = (char **)malloc((11) * sizeof(char *));
// 	envp[0] = ft_strdup("CHARSET=UTF-8");
// 	envp[1] = ft_strdup("HOSTNAME=a4d647f5f42a");
// 	envp[2] = ft_strdup("PWD=/pwd/desktop/minishell");
// 	envp[3] = ft_strdup("HOME=/root");
// 	envp[4] = ft_strdup("LANG=C.UTF-8");
// 	envp[5] = ft_strdup("TERM=xterm");
// 	envp[6] = ft_strdup("SHLVL=2");
// 	envp[7] = ft_strdup("LC_COLLATE=C");
// 	envp[8] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
// 	envp[9] = ft_strdup("_=/usr/bin/env");
// 	envp[10] = NULL;

//     update_old_pwd(envp);
    
// }

// // TEST(update_pwd)