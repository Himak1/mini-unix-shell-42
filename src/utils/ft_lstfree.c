/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstfree.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 12:13:49 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/20 12:44:52 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstfree(t_token *tokenlist)
{
	t_token	*tmp;

	while (tokenlist != NULL)
	{
		tmp = tokenlist->next;
		free(tokenlist->value);
		free(tokenlist);
		tokenlist = tmp;
	}
}
