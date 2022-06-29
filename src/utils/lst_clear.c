/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_clear.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:58:02 by jhille        #+#    #+#                 */
/*   Updated: 2022/06/29 17:08:06 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

void	lst_clear(t_token **list)
{
	t_token	*iter;
	t_token	*next;

	iter = *list;
	while (iter)
	{
		next = iter->next;
		free(iter->value);
		free(iter);
		if (next)
			iter = next;
	}
}
