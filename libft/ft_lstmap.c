/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 20:21:36 by jhille        #+#    #+#                 */
/*   Updated: 2020/11/26 21:42:04 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*ret;
	void	*ptr;

	if (!f || !lst)
		return (NULL);
	ptr = (*f)(&lst->content);
	ret = ft_lstnew(ptr);
	if (ret == NULL)
		return (NULL);
	if (lst->next != NULL)
	{
		ret->next = ft_lstmap(lst->next, f, del);
		if (ret->next == NULL)
		{
			(*del)(lst->content);
			ft_lstclear(&ret, del);
			return (NULL);
		}
	}
	return (ret);
}
