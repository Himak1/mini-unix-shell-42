/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 13:29:19 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/01 15:34:41 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "utils.h"

typedef unsigned int	t_uint;

t_uint	get_type(char *value);



void create_token(t_token **token_list, char *str, int start, int end);

#endif
