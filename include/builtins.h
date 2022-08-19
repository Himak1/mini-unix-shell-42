/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 12:43:48 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/19 19:01:14 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "parser.h"

void		pwd(void);

int	echo(char **arg);
int		check_n(char *arg);
int		get_index_arg(char **arg);
char	**extract_args(t_ast *cmd);

int	is_builtin(t_ast *exec_block, t_uint cmd_count);
int exec_builtin(t_ast *exec_block, char *envp[]);

void update_underscore(t_ast *cmd, char *envp[]);
void update_pwd(char *cmd, char *envp[]);
void update_old_pwd(char *envp[]);
char	**set_var(char *name, char *envp[]);

int	exec_echo(t_ast *cmd, char *envp[]);
int	exec_cd(t_ast *cmd, char *envp[]);
int	exec_pwd(t_ast *cmd, char *envp[]);
int	exec_env(t_ast *cmd, char *envp[]);
// int	exec_unset(t_ast *cmd, char *envp[]);
// int	exec_export(t_ast *cmd, char *envp[]);
// int	exec_exit(t_ast *cmd, char *envp[]);


#endif
