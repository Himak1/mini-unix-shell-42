/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_append.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 17:03:00 by jhille        #+#    #+#                 */
/*   Updated: 2022/06/29 17:08:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	lst_append(t_token **list, t_token *node)
{
	t_token	*iter;

	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = node;
}
