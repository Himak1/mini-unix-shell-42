/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_insert_back.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: Tessa <tvan-der@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/16 16:40:43 by Tessa         #+#    #+#                 */
/*   Updated: 2022/07/01 14:39:45 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/utils.h"

void	ft_lst_insert_back(t_token **token_list, t_uint type, char *value)
{
	t_token	*new;
	t_token	*current;

	new = lst_new(data);
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}
