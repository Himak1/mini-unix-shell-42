/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 21:25:10 by jhille        #+#    #+#                 */
/*   Updated: 2020/11/26 21:42:40 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*ptr;

	ptr = lst;
	i = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
