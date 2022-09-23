/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_xmalloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 11:25:51 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/23 11:30:36 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_xmalloc(size_t bytes)
{
	void	*output;

	output = malloc(bytes);
	if (!output)
		exit(EXIT_FAILURE);
	return (output);
}
