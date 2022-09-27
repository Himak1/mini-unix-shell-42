/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_cmd_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:44:30 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/27 12:06:37 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "executor.h"
#include "error_handling.h"

#include <stdio.h>
static char	*concatenate_path(const char *path_dir, const char *cmd)
{
	t_uint	total_len;
	char	*cmd_with_path;

	total_len = ft_strlen(path_dir) + ft_strlen(cmd) + 2;
	cmd_with_path = ft_xmalloc(total_len * sizeof(char));
	ft_strlcpy(cmd_with_path, path_dir, total_len);
	ft_strlcat(cmd_with_path, "/", total_len);
	ft_strlcat(cmd_with_path, cmd, total_len);
	return (cmd_with_path);
}

static int	try_paths(char **cmd, char **split_path)
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
			return (0);
		}
		free(tmp);
		i++;
	}
	return (-1);
}

static void	is_dir(char *cmd)
{
	struct stat	file;

	stat(cmd, &file);
	if (S_ISDIR(file.st_mode))
		cmd_custom_exit(cmd, IS_DIR);
}

void	add_cmd_path(char **cmd, char *envv[])
{
	char	*path;
	char	**split_path;

	if (ft_strchr(cmd[0], '/'))
	{
		is_dir(cmd[0]);
		if (access(cmd[0], F_OK) || access(cmd[0], X_OK))
			cmd_error_exit(cmd[0]);
		return ;
	}
	path = ft_getenv(envv, "PATH");
	if (path)
	{
		split_path = ft_split(path, ':');
		if (!split_path)
			exit(EXIT_FAILURE);
		if (try_paths(cmd, split_path))
			cmd_custom_exit(cmd[0], NOT_FOUND);
	}
	else
	{
		errno = ENOENT;
		cmd_error_exit(cmd[0]);
	}
}
