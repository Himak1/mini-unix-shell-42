/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 12:41:17 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/04 14:44:41 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_ast
{
	int				value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif
