/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 15:37:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/30 16:18:05 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

t_uint	get_type(char *value)
{
	t_uint	type;

	if (!ft_strncmp(value, "<", ft_strlen(value)))
		type = RDR_IN;
	else if (!ft_strncmp(value, ">", ft_strlen(value)))
		type = RDR_OUT;
	else if (!ft_strncmp(value, "<<", ft_strlen(value)))
		type = RDR_DLM_IN;
	else if (!ft_strncmp(value, ">>", ft_strlen(value)))
		type = RDR_APND_OUT;
	else if (!ft_strncmp(value, "|", ft_strlen(value)))
		type = PIPE;
	else
		type = WORD;
	return (type);
}

t_token	*create_token(char *value)
{
	t_token	*new;

	new = ft_xmalloc(sizeof(t_token));
	new->value = ft_xstrdup(value);
	new->type = get_type(value);
	new->next = NULL;
	return (new);
}

void	create_tokenlist(t_token **token_list, char **str)
{
	int		i;
	t_token	*new;

	i = 0;
	while (str[i] != NULL)
	{
		new = create_token(str[i]);
		if (*token_list == NULL)
			*token_list = new;
		else
			lst_add_bk(token_list, new);
		i++;
	}
}

void	ft_lexer(t_token **tokenlist, char *input)
{
	char	**split_commands;

	split_commands = split_command_line(input);
	if (!split_commands)
		return ;
	create_tokenlist(tokenlist, split_commands);
	ft_free_2d_array(split_commands);
}
