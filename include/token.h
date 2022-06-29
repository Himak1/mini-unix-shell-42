/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:36:49 by jhille        #+#    #+#                 */
/*   Updated: 2022/06/29 16:49:23 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef unsigned int	t_uint;

enum e_types
{
	string = 0,
	single_quote = 1,
	double_quote = 2
};

typedef struct s_token
{
	t_uint		type;
	char		*value;
	t_token		*next;
}				t_token;

#endif
