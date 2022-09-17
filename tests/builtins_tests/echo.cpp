// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   echo.cpp                                           :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2022/08/15 14:08:50 by tvan-der      #+#    #+#                 */
// /*   Updated: 2022/09/12 15:58:04 by tvan-der      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "gtest/gtest.h"

// extern "C" {
// #include "utils.h"
// #include "builtins.h"
// #include "parser.h"
// #include "lexer.h"
// #include "expander.h"
// }

// TEST(check_n, basic_test1)
// {
//     char *test = "hello";

//     int i = check_n(test);
//     ASSERT_EQ(0, i);
// }

// TEST(check_n, basic_test2)
// {
//     char *test = "-n";

//     int i = check_n(test);
//     ASSERT_EQ(1, i);
// }

// TEST(check_n, basic_test3)
// {
//     char *test = "-nnnn";

//     int i = check_n(test);
//     ASSERT_EQ(1, i);
// }

// TEST(check_n, basic_test4)
// {
//     char *test = "-n -n";

//     int i = check_n(test);
//     ASSERT_EQ(1, i);
// }

// TEST(get_index_arg, basic_test1)
// {
//     char input[] = "echo hello";

//     char **args = NULL;
//     t_token *lst;
// 	t_ast   *tree;
//     char **envp = create_envp();
    
// 	lst = NULL;
// 	ft_lexer(&lst, input);
// 	tree = parse_tokens(lst);
// 	expand_tree(tree, envp);
//     tree = tree->child_node->child_node;
//     while (tree->type != CMD)
//         tree->next_sib_node;
//     tree = tree->child_node;

//     int i = get_index_arg(tree);
//     ASSERT_EQ(1, i);
// }

// TEST(get_index_arg, basic_test2)
// {
//     char input[] = "echo -n hello";

//     char **args = NULL;
//     t_token *lst;
// 	t_ast   *tree;
//     char **envp = create_envp();
    
// 	lst = NULL;
// 	ft_lexer(&lst, input);
// 	tree = parse_tokens(lst);
// 	expand_tree(tree, envp);
//     tree = tree->child_node->child_node;
//     while (tree->type != CMD)
//         tree->next_sib_node;
//     tree = tree->child_node;

//     int i = get_index_arg(tree);
//     ASSERT_EQ(2, i);
// }

// TEST(get_index_arg, basic_test3)
// {
//     char input[] = "echo -nnn -nn hello";

//     char **args = NULL;
//     t_token *lst;
// 	t_ast   *tree;
//     char **envp = create_envp();
    
// 	lst = NULL;
// 	ft_lexer(&lst, input);
// 	tree = parse_tokens(lst);
// 	expand_tree(tree, envp);
//     tree = tree->child_node->child_node;
//     while (tree->type != CMD)
//         tree->next_sib_node;
//     tree = tree->child_node;

//     int i = get_index_arg(tree);
//     ASSERT_EQ(3, i);
// }

// TEST(get_index_arg, basic_test4)
// {
//     char input[] = "echo -nnn hi hello";

//     char **args = NULL;
//     t_token *lst;
// 	t_ast   *tree;
//     char **envp = create_envp();
    
// 	lst = NULL;
// 	ft_lexer(&lst, input);
// 	tree = parse_tokens(lst);
// 	expand_tree(tree, envp);
//     tree = tree->child_node->child_node;
//     while (tree->type != CMD)
//         tree->next_sib_node;
//     tree = tree->child_node;

//     int i = get_index_arg(tree);
//     ASSERT_EQ(2, i);
// }
// // TEST(extract_args, basic_test1)
// // {
// //     char input[] = "echo hello";

// //     char **args = NULL;
// //     t_token *lst;
// // 	t_ast   *tree;
// //     char **envp = create_envp();
    
// // 	lst = NULL;
// // 	ft_lexer(&lst, input);
// // 	tree = parse_tokens(lst);
// // 	expand_tree(tree, envp);
// //     tree = tree->child_node->child_node;
// //     while (tree->type != CMD)
// //         tree->next_sib_node;
// //     tree = tree->child_node;
// //     args = extract_args(tree);
// //     ASSERT_STREQ(args[0], "echo");
// //     ASSERT_STREQ(args[1], "hello");
// //     ASSERT_STREQ(args[2], nullptr);
// // }