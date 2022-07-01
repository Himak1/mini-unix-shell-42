/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
<<<<<<< HEAD
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:14:48 by jhille        #+#    #+#                 */
/*   Updated: 2020/11/22 16:54:09 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
=======
/*   By: tvan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 15:45:10 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/01 13:36:32 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/utils.h"

size_t	ft_strlen(const char *s)
>>>>>>> tvan-der
{
	size_t	i;

	i = 0;
<<<<<<< HEAD
	while (str[i] != '\0')
		i++;
=======
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
>>>>>>> tvan-der
	return (i);
}
