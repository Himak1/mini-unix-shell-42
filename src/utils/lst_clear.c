/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_clear.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:58:02 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/16 12:14:01 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

void	lst_clear(t_token *list)
{
	t_token	*iter;

	iter = list;
	while (iter)
	{
		free(iter);
		iter = iter->next;
	}
}
