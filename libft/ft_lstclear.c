/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 19:52:53 by jhille        #+#    #+#                 */
/*   Updated: 2020/11/26 21:39:14 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*iterate;
	t_list	*store;

	iterate = *(lst);
	while (iterate != NULL)
	{
		store = iterate->next;
		(*del)(iterate->content);
		free(iterate);
		iterate = store;
	}
	*(lst) = NULL;
}
