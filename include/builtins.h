/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 12:43:48 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/15 14:57:44 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "parser.h"

void		pwd(void);

void    echo(t_ast *cmd);
int		check_n(char *arg);
int		get_index_arg(t_ast *cmd);

char	**extract_args(t_ast *cmd);
char    *extract_var_value(char *env_var);
char    **add_var_to_env(char *str, char **arr);

int	is_builtin(t_ast *exec_block, t_uint cmd_count);
int exec_builtin(t_ast *exec_block, char *envp[]);

void update_underscore(t_ast *cmd, char *envp[]);
void update_pwd(char *envp[]);
char **update_old_pwd(char *envp[]);
char **add_oldpwd(char *envp[]);

int	exec_echo(t_ast *cmd, char *envp[]);
int	exec_cd(t_ast *cmd, char *envp[]);
int	exec_pwd(t_ast *cmd, char *envp[]);
int	exec_env(t_ast *cmd, char *envp[]);
// int	exec_unset(t_ast *cmd, char *envp[]);
int	exec_export(t_ast *cmd, char *envp[]);
// int	exec_exit(t_ast *cmd, char *envp[]);


void	print_envp(char **envp); //delete!!!!

#endif
