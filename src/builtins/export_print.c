/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 16:51:33 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/28 17:10:48 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include "error_handling.h"

static void	swap_in_place(char **prev_j, char **current_j)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = *prev_j;
	tmp2 = *current_j;
	*prev_j = tmp2;
	*current_j = tmp1;
}

static char	**sort_alpha(char *arr[], int size)
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
			if (ft_strncmp(sorted[j - 1], sorted[j],
					ft_strlen(sorted[j - 1])) > 0)
				swap_in_place(&sorted[j - 1], &sorted[j]);
			j++;
		}
		i++;
	}
	return (sorted);
}

void	print_with_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
	if (!str[i])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	ft_putchar_fd(str[i], STDOUT_FILENO);
	i++;
	ft_putchar_fd('"', STDOUT_FILENO);
	while (str[i] && str[i] != '=')
	{
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	print_export_list(char *envv[])
{
	int		envv_size;
	char	**sorted_envv;

	envv_size = 0;
	while (envv[envv_size])
		envv_size++;
	sorted_envv = sort_alpha(envv, envv_size);
	envv_size = 0;
	while (sorted_envv[envv_size])
	{
		if (ft_strncmp(sorted_envv[envv_size], "_=", ft_strlen("_=")))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			print_with_quotes(sorted_envv[envv_size]);
		}
		envv_size++;
	}
	ft_free_2d_array(sorted_envv);
}
