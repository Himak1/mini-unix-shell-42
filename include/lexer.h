/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 13:29:19 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/30 11:37:59 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "utils.h"

typedef unsigned int	t_uint;

t_uint	get_type(char *value);

void	create_tokenlist(t_token **token_list, char **str);
void	ft_lexer(t_token **token_list, char *input);
char	**split_command_line(char const *s);
int		count_tokens(char const *s);

#endif
