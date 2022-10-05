/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_command_line.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 15:03:07 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/10/05 18:00:56 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static	char	**fill_array(char **arr, char const *s, int len)
{
	int	i;
	int	j;

	j = 0;
	while (*s == ' ' && *s)
		s++;
	while (j < len)
	{
		i = 0;
		i = find_other(s, i);
		i++;
		arr[j] = ft_xmalloc(sizeof(char) * (i + 1));
		ft_strlcpy(arr[j], s, (i + 1));
		s += i;
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**split_command_line(char const *s)
{
	int		count;
	char	**split_arr;

	if (!s)
		return (NULL);
	count = count_tokens(s);
	split_arr = ft_xmalloc((count + 1) * sizeof(char *));
	split_arr = fill_array(split_arr, s, count);
	return (split_arr);
}
