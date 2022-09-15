/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 10:39:53 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/15 10:33:07 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "builtins.h"
#include <stdio.h>

char *extract_var_value(char *env_var)
{
	char *value;
	char **key_and_value;
	
	key_and_value = ft_split(env_var, '=');
	value = ft_strdup(key_and_value[1]);
	ft_free_2d_array(key_and_value);
	return(value);
}


char	**extract_args(t_ast *cmd)
{
	int i;
	int len;
	t_ast *iter;
	char **args;

	i = 0;
	len = 0;
	iter = cmd;
	while (iter->next_sib_node != NULL)
	{
		len++;
		iter = iter->next_sib_node;
	}
	args = (char **)malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	iter = cmd;
	while (i < (len + 1))
	{
		args[i] = ft_strdup(iter->value);
		iter = iter->next_sib_node;
		i++;
	}
	args[i] = NULL;
	return (args);
}