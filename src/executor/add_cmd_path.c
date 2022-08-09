/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_cmd_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:44:30 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/09 12:04:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "executor.h"

#include <stdio.h>

static char	*concatenate_path(const char *path_dir, const char *cmd)
{
	t_uint	total_len;
	char	*cmd_with_path;

	total_len = ft_strlen(path_dir) + ft_strlen(cmd) + 2;
	cmd_with_path = xmalloc(total_len * sizeof(char));
	ft_strlcpy(cmd_with_path, path_dir, total_len);
	ft_strlcat(cmd_with_path, "/", total_len);
	ft_strlcat(cmd_with_path, cmd, total_len);
	return (cmd_with_path);
}

static void	try_paths(char **cmd, char **split_path)
{
	int		i;
	int		status;
	char	*tmp;

	i = 0;
	while (split_path[i])
	{
		tmp = concatenate_path(split_path[i], cmd[0]);
		status = access(tmp, F_OK);
		if (status == 0)
		{
			free(cmd[0]);
			cmd[0] = tmp;
			return ;
		}
		free(tmp);
		i++;
	}
}

void	add_cmd_path(char **cmd)
{
	char	*path;
	char	**split_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd[0], '/'))
		return ;
	path = getenv("PATH");
	if (path)
	{
		split_path = ft_split(path, ':');
		if (!split_path)
			exit(EXIT_FAILURE);
		try_paths(cmd, split_path);
	}
}
