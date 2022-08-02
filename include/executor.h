/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:30:21 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/02 14:01:09 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"

typedef struct s_exec {
	int		pip1[2];
	int		pip2[2];
	int		pid;
	int		fd_in;
	int		fd_out;
	char	**cmd;
}			t_exec;

int	executor(t_ast *ast, t_uint cmd_count);

int	getfd_in(t_ast *exec_block);
int	getfd_out(t_ast *exec_block);

#endif