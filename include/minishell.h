/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 11:53:21 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/22 13:37:29 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <termios.h>
# include "parser.h"

typedef struct s_data
{
	struct termios		config;
	t_token				*lst;
	t_ast				*tree;
	char				**envv;
	struct sigaction	sigint_h;
}						t_data;

#endif
