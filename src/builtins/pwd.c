/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 12:43:21 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/26 14:44:14 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	pwd(void)
{
	char	*env_var;

	env_var = getenv("PWD");
	if (env_var)
	{
		if (printf("%s", env_var) == -1)
			exit(EXIT_FAILURE);
	}
	else
		return (-1);
	return (0);
}
