/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 13:29:19 by jhille        #+#    #+#                 */
/*   Updated: 2022/10/05 17:49:52 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "utils.h"

typedef unsigned int	t_uint;

t_uint	get_type(char *value);

int		create_tokenlist(t_token **token_list, char **str);
int		check_syntax_error(t_token **list);
void	ft_lexer(t_token **token_list, char *input);
char	**split_command_line(char const *s);

int		count_tokens(char const *s);
int		find_quotes(const char *s, int i);
int		find_other(const char *s, int i);
int		get_ctype(char c);
#endif
