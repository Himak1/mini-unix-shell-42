/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 11:53:21 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/13 11:00:46 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>

typedef struct s_data
{
	t_token				*lst;
	t_ast				*tree;
	char				**envv;
	struct sigaction	sigint_h;
}						t_data;

#endif
