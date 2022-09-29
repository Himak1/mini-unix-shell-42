/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_command_line.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 15:03:07 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/29 10:38:55 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdio.h>

int	find_quotes(const char *s, int i)
{
	int	new_i;
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	if (!s)
		return (0);
	while (s[i] != ' ' && s[i] != '\0' && (dquote != 2 || squote != 2))
	{
		if (s[i] == '\"' && !squote)
			dquote++;
		if (s[i] == '\'' && !dquote)
			squote++;
		i++;
		while (s[i] == ' ' && (dquote == 1 || squote == 1))
			i++;
	}
	new_i = i;
	return (new_i);
}

int	count_tokens(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == ' ' && s[i] != '\0')
			i++;
		i = find_quotes(s, i);
		count++;
	}
	if (i != 0 && s[i - 1] == ' ')
		count--;
	return (count);
}

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
		i = find_quotes(s, i);
		arr[j] = ft_xmalloc(sizeof(char) * (i + 1));
		ft_strlcpy(arr[j], s, (i + 1));
		while (s[i] == ' ' && s[i])
			i++;
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
