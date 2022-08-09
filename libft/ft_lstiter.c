/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 19:54:46 by jhille        #+#    #+#                 */
/*   Updated: 2021/02/21 23:45:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	t_list	*iterate;

	iterate = lst;
	while (iterate != NULL)
	{
		(*f)(iterate->content);
		iterate = iterate->next;
	}
}
