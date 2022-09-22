/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_exitcode.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 18:35:23 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/21 14:42:29 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

int	get_exitcode(int status)
{
	int	exitcode;

	exitcode = 0;
	if (WIFEXITED(status))
		exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exitcode = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		exitcode = WSTOPSIG(status) + 128;
	return (exitcode);
}
