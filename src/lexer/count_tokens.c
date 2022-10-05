/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 17:21:31 by jhille        #+#    #+#                 */
/*   Updated: 2022/10/05 17:27:40 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	find_quotes(const char *s, int i)
{
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	if (!s)
		return (0);
	while (s[i] && (dquote != 2 && squote != 2))
	{
		if (s[i] == '\"' && !squote)
			dquote++;
		if (s[i] == '\'' && !dquote)
			squote++;
		if (dquote != 2 && squote != 2)
			i++;
	}
	return (i);
}

int	get_ctype(char c)
{
	int	output;

	if (c == '<')
		output = 0;
	else if (c == '>')
		output = 1;
	else if (c == '|')
		output = 2;
	else if (c == ' ')
		output = 3;
	else if (c == '\0')
		output = 4;
	else
		output = 5;
	return (output);
}

int	find_other(const char *s, int i)
{
	int	ctype;
	int	old_ctype;

	old_ctype = get_ctype(s[i]);
	while (s[i])
	{
		ctype = get_ctype(s[i]);
		if (ctype != old_ctype)
			break ;
		i++;
	}
	if (i != 0)
		i--;
	return (i);
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
		if (s[i] == '\'' || s[i] == '\"')
			i = find_quotes(s, i);
		else
			i = find_other(s, i);
		count++;
		i++;
	}
	if (i != 0 && s[i - 1] == ' ')
		count--;
	return (count);
}
