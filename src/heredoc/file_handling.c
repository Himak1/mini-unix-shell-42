/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:07:42 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/21 16:57:49 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

/*
	Returns a string containing a path to a directory for temporary files
*/
char	*find_tmp_filepath(void)
{
	char	*tmpdir;
	char	*env;

	env = getenv("TMPDIR");
	if (!env)
		tmpdir = ft_strdup("/tmp/");
	else
		tmpdir = ft_strdup(env);
	if (!tmpdir)
		exit(EXIT_FAILURE);
	return (tmpdir);
}

char	*create_tmp_filename(char *tmp_filepath, int i)
{
	char	*file_with_path;
	char	*filename;
	char	*number;

	number = ft_itoa(i);
	if (!number)
		exit(EXIT_FAILURE);
	filename = ft_strjoin("minishell_heredoc_rd_", number);
	if (!filename)
		exit(EXIT_FAILURE);
	file_with_path = ft_strjoin(tmp_filepath, filename);
	if (!file_with_path)
		exit(EXIT_FAILURE);
	free(number);
	free(filename);
	return (file_with_path);
}
