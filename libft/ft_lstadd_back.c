/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 22:38:13 by jhille        #+#    #+#                 */
/*   Updated: 2020/11/26 21:39:50 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (temp == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
