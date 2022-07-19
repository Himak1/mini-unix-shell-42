/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 12:41:17 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/19 11:49:52 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "utils.h"

enum e_ast_types
{
	EXEC_CHAIN = 20,
	BASE,
	ADD_BASE,
	EXEC_BLOCK,
	RDS,
	RD_IN,
	RD_OUT,
	RD_DE,
	RD_AP,
	CMD,
	TERMINAL,
};

typedef struct s_ast
{
	t_uint			type;
	int				num_children;
	char			*value;
	struct s_ast	*child_node;
	struct s_ast	*next_sib_node;
	struct s_ast	*prev_sib_node;
}					t_ast;

t_ast	*parse_tokens(t_token **list);

t_ast	*parse_pipe(t_token **list);

t_ast	*exec_block(t_token **list);
t_ast	*parse_cmd(t_token **list);

int		rds(t_ast *parent, t_token **list);
t_ast	*rd_in(t_token **list);
t_ast	*rd_out(t_token **list);

t_uint	peek_tkn(t_token *token);
t_uint	next_2_tkn(t_token *token, t_uint type1, t_uint type2);

void	free_child_nodes(t_ast *parent);

t_ast	*new_node(int type);
t_ast	*new_term_node(t_token **list);
int		add_child(t_ast *parent, t_ast *child);

#endif
