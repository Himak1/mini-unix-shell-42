/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_cmd_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:44:30 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/05 17:25:22 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	try_paths(char **cmd, char **split_path)
{
	int	i;
}

int	add_cmd_path(char **cmd)
{
	char	*path;
	char	**split_path;
	int		i;

	i = 0;
	if (!ft_strchr(cmd[0], '/'))
		return (0);
	path = getenv("PATH");
	if (!path)
	{
		split_path = ft_split(path, ':');
		if (!split_path)
			exit(EXIT_FAILURE);
		return (try_paths(cmd, split_path));
	}
	return (0);
}
