/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/22 14:02:54 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/25 16:46:49 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	spltnum(char const *str, char c)
{
	int		i;
	int		sc;

	i = 0;
	sc = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == c && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] != c && str[i] != '\0')
			i++;
		if (str[i] == c)
			sc++;
		while (str[i] == c && str[i] != '\0')
			i++;
	}
	if (str[i - 1] == c || (str[i] == c && c == '\0'))
		sc--;
	return (sc + 1);
}

static void	cleanup(char **ret)
{
	int		i;

	i = 0;
	while (ret[i] != 0)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}

static int	writearr(char const *str, char c, int sc, char **ret)
{
	int		j;
	int		i;
	int		start;

	j = 0;
	i = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	while (j < sc)
	{
		start = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		ret[j] = ft_substr(str, start, (i - start));
		if (ret[j] == NULL)
			return (0);
		while (str[i] == c && str[i] != '\0')
			i++;
		j++;
	}
	return (1);
}

char	**ft_split(char const *str, char c)
{
	char	**ret;
	int		sc;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	sc = spltnum(str, c);
	ret = ft_calloc((sc + 1), sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (str[i] == c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		ret[0] = 0;
		return (ret);
	}
	i = writearr(str, c, sc, ret);
	if (i == 0)
	{
		cleanup(ret);
		return (NULL);
	}
	return (ret);
}
