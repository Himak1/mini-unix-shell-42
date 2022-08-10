/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 22:38:13 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/10 13:28:27 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *_new)
{
	t_list	*temp;

	temp = *lst;
	if (temp == NULL)
	{
		*lst = _new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = _new;
}
