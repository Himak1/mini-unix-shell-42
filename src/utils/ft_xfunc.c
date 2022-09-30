/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_xfunc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 15:52:09 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/30 16:18:33 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**ft_xsplit(char *str, char delim)
{
	char	**output;

	output = ft_split(str, delim);
	if (!output)
		exit(EXIT_FAILURE);
	return (output);
}

char	*ft_xstrdup(char *str)
{
	char	*output;

	output = ft_strdup(str);
	if (!output)
		exit(EXIT_FAILURE);
	return (output);
}

char	*ft_xstrjoin(char *str1, char *str2)
{
	char	*output;

	output = ft_strjoin(str1, str2);
	if (!output)
		exit(EXIT_FAILURE);
	return (output);
}
