/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:18:49 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/15 15:12:04 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "expander.h"
#include "builtins.h"
#include <limits.h>
#include <stdio.h>

// if env is called _=/usr/bin/env
// anything else, expand to last arg of last used command (last terminal in ast)

// char **add_var_to_env_list(char *var_name, char *envp[])
// {
// 	int i;
// 	char **new_arr;

// 	i = 0;
// 	while (envp[i] != NULL)
// 		i++;
// 	new_arr = (char **)malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		new_arr[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	new_arr[i] = ft_strdup(var_name);
// 	i++;
// 	new_arr[i] = NULL;
// 	ft_free_2d_array(envp);
// 	return (new_arr);
// }

int ft_len_2d_arr(char **arr)
{
	int i;
	
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

// void update_underscore(t_ast *cmd, char *envp[])
// {

// }

// int main()
// {
// 	char input[] = "echo -nnn -nn hello";

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
	
// }

void update_underscore(t_ast *cmd, char *envp[])
{
	int		index;
	int		len_envp;
    t_ast	*iter;
	char	*last_arg;

    iter = cmd;
	last_arg = NULL;
	len_envp = ft_len_2d_arr(envp);
	printf("len of envp %d\n", len_envp);
	index = ft_get_index_2d(envp, "_=");
	printf("index underscore %d\n", index);
	if (ft_strncmp(envp[index], "_=", ft_strlen(envp[index])))
		envp = add_var_to_env("_=", envp);
	free(envp[index]);
	if (!ft_strncmp(iter->value, "env", ft_strlen(iter->value)))
		envp[index] = ft_strdup("_=/usr/bin/env");
	else
	{
		while (iter->next_sib_node != NULL)
			iter = iter->next_sib_node;
		last_arg = ft_strdup(iter->value);
		envp[index]= ft_strjoin("_=", last_arg);
		free(last_arg);
	}
}

// void update_pwd(char *envp[])
// {
// 	int		index;
// 	char	*new_path;
// 	char cwd[PATH_MAX];
	
// 	new_path = NULL;
// 	index = ft_get_index_2d(envp, "PWD=");
// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 		new_path = ft_strdup(cwd);
// 	else
// 		perror("cd:");
// 	// if (envp[index])
// 	// 	free(envp[index]); // error with this?
// 	envp[index]= ft_strjoin("PWD=", new_path);
// 	free(new_path);
// }

// char	**update_old_pwd(char *envp[])
// {
// 	int index_old_pwd;
// 	int index_pwd;
// 	char *old_path;

// 	index_old_pwd = ft_get_index_2d(envp, "OLDPWD=");
// 	if (!index_old_pwd && !ft_strnstr(envp[index_old_pwd], "OLDPWD=", ft_strlen(envp[index_old_pwd])))
// 		envp = add_oldpwd(envp);
// 	index_pwd = ft_get_index_2d(envp, "PWD=");
// 	old_path = extract_var_value(envp[index_pwd]);
// 	index_old_pwd = ft_get_index_2d(envp, "OLDPWD=");
// 	free(envp[index_old_pwd]);
// 	envp[index_old_pwd] = ft_strjoin("OLDPWD=", old_path);
// 	free(old_path);
// 	return(envp);
// }