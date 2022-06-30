/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_add_ft.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 10:59:20 by jhille        #+#    #+#                 */
/*   Updated: 2022/06/30 11:01:38 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	lst_add_ft(t_token **list, t_token *node)
{
	t_token	*front;

	front = *list;
	*list = node;
	node->next = front;
}