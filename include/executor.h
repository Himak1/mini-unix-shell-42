/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:30:21 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/20 16:46:44 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"

typedef struct s_exec {
	t_uint			cmd_count;
	int				pip1[2];
	int				pip2[2];
	int				*pid;
	int				fd_in;
	int				fd_out;
	char			**cmd;
}					t_exec;

int		executor(t_ast *tree, char **envv[]);
void	executor_loop(t_ast *exec_block, t_exec *data, char *envv[]);
void	handle_redirects(t_exec *data, t_uint i);

void	init_pipes(int *pip1, int *pip2);
void	close_pipe(t_exec *data, t_uint i);
void	choose_pipe(t_exec *data, t_uint i);

void	extract_ast_data(t_ast *exec_block, t_exec *data);

int		getfd_in(t_ast *exec_block);
int		getfd_out(t_ast *exec_block);
char	**getcmd(t_ast *exec_block);
void	add_cmd_path(char **cmd);

#endif
