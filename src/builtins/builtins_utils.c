/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 10:39:53 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/16 11:14:10 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "builtins.h"
#include <stdio.h>

// char *extract_var_value(char *env_var)
// {
// 	char *value;
// 	char **key_and_value;
	
// 	key_and_value = ft_split(env_var, '=');
// 	value = ft_strdup(key_and_value[1]);
// 	ft_free_2d_array(key_and_value);
// 	return(value);
// }

// void update_var(t_ast *cmd, char **envv[], char *var)
// {
// 	int i;
// 	char **temp;
	
// 	i = 0;
// 	temp = *envv;
// 	while (temp[i] && !ft_strnstr(temp[i], var, ft_strlen(temp[i])))
// 	{
		
// 	}
// 	if (temp[i]) // var is found, change var at that position
	
// 	else // var is not found, add var at the bottom
// 		add_var_to_env()
// }


