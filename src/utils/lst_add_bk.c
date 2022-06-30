/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_add_bk.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 17:03:00 by jhille        #+#    #+#                 */
/*   Updated: 2022/06/30 10:58:55 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	lst_add_bk(t_token **list, t_token *node)
{
	t_token	*iter;

	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = node;
}
