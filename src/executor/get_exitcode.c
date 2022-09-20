/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_exitcode.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 18:35:23 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/20 18:41:22 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

int	get_exitcode(int status)
{
	int	exitcode;

	if (WIFEXITED(status))
		exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exitcode = WTERMSIG(status);
	else if (WIFSTOPPED(status))
		exitcode = WSTOPSIG(status);
	else
		exitcode = 131;
	return (exitcode);
}
