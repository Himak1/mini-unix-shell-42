/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 15:37:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/10/06 11:12:29 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_lexer(t_token **tokenlist, char *input)
{
	char	**split_commands;
	int		status;

	split_commands = split_command_line(input);
	if (!split_commands)
		return ;
	status = create_tokenlist(tokenlist, split_commands);
	ft_free_2d_array(split_commands);
	if (status == -1)
	{
		ft_lstfree(*tokenlist);
		*tokenlist = NULL;
	}
}
