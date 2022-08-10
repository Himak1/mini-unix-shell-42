/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 14:55:42 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/21 23:46:57 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	rmcheck(char c, char const *rm)
{
	int	itrm;
	int	rmlen;
	int	check;

	itrm = 0;
	rmlen = 0;
	check = 0;
	while (rm[rmlen] != '\0')
		rmlen++;
	while (rm[itrm] != '\0')
	{
		if (rm[itrm] == c)
			check++;
		itrm++;
	}
	if ((itrm - check) != rmlen)
		return (1);
	return (0);
}

static int	chklenfd(char const *str, char const *rm)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (rmcheck(str[i], rm) == 0)
			return (i);
		i++;
	}
	return (0);
}

static int	chklenrev(char const *str, char const *rm)
{
	int	r;

	r = 0;
	while (str[r] != '\0')
		r++;
	while (r > 0)
	{
		if (rmcheck(str[r - 1], rm) == 0)
			return (r);
		r--;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *rm)
{
	int		i;
	int		r;
	int		maxlen;
	char	*ret;

	if (str == 0 || rm == 0)
		return (NULL);
	i = chklenfd(str, rm);
	r = chklenrev(str, rm);
	maxlen = r - i;
	r = 0;
	ret = malloc((maxlen + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (r < maxlen)
	{
		ret[r] = str[i];
		r++;
		i++;
	}
	ret[maxlen] = '\0';
	return (ret);
}
