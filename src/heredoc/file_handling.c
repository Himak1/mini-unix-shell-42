/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:07:42 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/27 17:30:53 by jhille        ########   odam.nl         */
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

static char	*create_ttyname(void)
{
	char	*tty_stack;
	char	*tty_no_path;

	tty_stack = ft_strrchr(ttyname(STDOUT_FILENO), '/');
	if (!tty_stack)
		exit(EXIT_FAILURE);
	tty_no_path = ft_strdup(tty_stack + 1);
	if (!tty_no_path)
		exit(EXIT_FAILURE);
	return (tty_no_path);
}

char	*create_tmp_filename(char *tmp_filepath, int i)
{
	char	*file_with_path;
	char	*filename;
	char	*number;
	char	*tty;

	tty = create_ttyname();
	number = ft_itoa(i);
	if (!number)
		exit(EXIT_FAILURE);
	filename = ft_strjoin(number, tty);
	if (!filename)
		exit(EXIT_FAILURE);
	file_with_path = ft_strjoin(tmp_filepath, filename);
	if (!file_with_path)
		exit(EXIT_FAILURE);
	free(number);
	free(filename);
	free(tty);
	return (file_with_path);
}
