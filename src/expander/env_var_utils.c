/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 11:41:44 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/30 16:03:49 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "expander.h"

int	get_env_var_len(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != ' ' && env_var[i] != '\0')
	{
		i++;
		if (env_var[i] == '$' || env_var[i] == '\"' || env_var[i] == '\'')
			break ;
	}
	return (i);
}

char	**get_env_var(char *input, int *exit_code)
{
	int		i;
	int		len;
	int		count;
	char	**env_var;

	i = 0;
	count = count_dollar_sign(input, exit_code);
	if (!count || *exit_code == -1)
		return (NULL);
	env_var = ft_xmalloc(sizeof(char *) * (count + 1));
	while (*input && i < count)
	{
		if (*input == '$')
		{
			len = get_env_var_len(input);
			env_var[i] = ft_xmalloc(sizeof(char *) * (len + 1));
			ft_strlcpy(env_var[i], input, (len + 1));
			i++;
		}
		input++;
	}
	env_var[i] = NULL;
	return (env_var);
}

t_env_var	*create_env_var(char *value)
{
	t_env_var	*new;

	new = ft_xmalloc(sizeof(t_env_var));
	new->env_value = ft_xstrdup(value);
	new->len_env = ft_strlen(new->env_value);
	new->len_exp = 0;
	new->exp_env = NULL;
	new->next = NULL;
	return (new);
}

void	lst_add_bk_env_var(t_env_var **list, t_env_var *env_var)
{
	t_env_var	*iter;

	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = env_var;
}

void	create_env_var_list(t_env_var **env_var_list, char **env_var)
{
	int			i;
	t_env_var	*new;

	i = 0;
	while (env_var[i] != NULL)
	{
		new = create_env_var(env_var[i]);
		if (*env_var_list == NULL)
			*env_var_list = new;
		else
			lst_add_bk_env_var(env_var_list, new);
		i++;
	}
	ft_free_2d_array(env_var);
}
