/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 12:41:17 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/05 17:06:32 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum e_ast_types
{
	EXE_CHAIN,
	BASE,
	ADD_BASE,
	EXE_BLOCK,
	RDS,
	RD_IN,
	RD_OUT,
	OPERATOR,
	CMD,
	CMD_NAME,
	CMD_ARG,
};

typedef struct s_ast
{
	int				type;
	int				num_children;
	char			*value;
	struct s_ast	*child_node;
	struct s_ast	*next_sib_node;
	struct s_ast	*prev_sib_node;
}					t_ast;

t_ast	*new_node(int type);
int		add_child(t_ast *parent, t_ast *child);

#endif
