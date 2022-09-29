/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_2d_alpha.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 16:23:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/27 16:32:45 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

static void	sort_alpha(char *sorted[], int index)
{
	char	*temp;

	temp = NULL;
	if (ft_strncmp(sorted[index - 1], sorted[index],
			ft_strlen(sorted[index - 1])) > 0)
	{
		temp = ft_strdup(sorted[index - 1]);
		free(sorted[index - 1]);
		sorted[index - 1] = ft_strdup(sorted[index]);
		free(sorted[index]);
		sorted[index] = ft_strdup(temp);
		free(temp);
	}
}

char	**sort_2d_alpha(char *arr[], int size)
{
	int		i;
	int		j;
	char	**sorted;

	sorted = cpy_2d(arr);
	i = 1;
	while (i < size)
	{
		j = 1;
		while (j < size)
		{
			sort_alpha(sorted, j);
			j++;
		}
		i++;
	}
	return (sorted);
}
