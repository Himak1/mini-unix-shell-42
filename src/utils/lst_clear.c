/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_clear.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:58:02 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/16 13:29:55 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

void	lst_clear(t_token *list)
{
	t_token	*iter;
	t_token	*prev;

	iter = list;
	while (iter)
	{
		prev = iter;
		iter = iter->next;
		free(prev);
	}
}
