/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 20:23:03 by jhille        #+#    #+#                 */
/*   Updated: 2021/11/21 22:38:57 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*strct_ptr;

	strct_ptr = (t_list *)malloc(sizeof(t_list));
	if (strct_ptr == NULL)
		return (NULL);
	strct_ptr->content = content;
	strct_ptr->next = NULL;
	return (strct_ptr);
}
