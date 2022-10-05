/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokenlist.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 17:29:40 by jhille        #+#    #+#                 */
/*   Updated: 2022/10/05 17:53:32 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_valid_token(const char *s)
{
	int		ctype;
	t_uint	length;

	length = ft_strlen(s);
	ctype = get_ctype(s[0]);
	if ((ctype == 0 || ctype == 1) && length > 2)
		return (-1);
	else if (ctype == 2 && length > 1)
		return (-1);
	else if (ctype == 3)
		return (0);
	else
		return (1);
}

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
	new->value = ft_strdup(value);
	if (!new->value)
		exit(EXIT_FAILURE);
	new->type = get_type(value);
	new->next = NULL;
	return (new);
}

int	create_tokenlist(t_token **token_list, char **str)
{
	int		i;
	int		status;
	t_token	*new;

	i = 0;
	while (str[i] != NULL)
	{
		status = is_valid_token(str[i]);
		if (status == -1)
			return (-1);
		else if (status == 1)
		{
			new = create_token(str[i]);
			if (*token_list == NULL)
				*token_list = new;
			else
				lst_add_bk(token_list, new);
		}
		i++;
	}
	return (0);
}
