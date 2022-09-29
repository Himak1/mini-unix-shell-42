/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 16:37:19 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/27 16:55:23 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

int	error_unclosed_quote(void)
{
	ft_putendl_fd("Syntax error: unclosed quote", STDERR_FILENO);
	return (-1);
}
