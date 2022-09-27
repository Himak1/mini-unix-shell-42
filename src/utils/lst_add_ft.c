/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_add_ft.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 10:59:20 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/26 14:46:58 by tvan-der      ########   odam.nl         */
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
