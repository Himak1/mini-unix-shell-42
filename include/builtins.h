/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 12:43:48 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/28 17:09:04 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"

int		check_n(char *arg);
int		get_index_arg(t_ast *cmd);

void	push_var_to_env(char *str, char **arr[]);
void	pop_var_from_env(char **arr[], int index);
void	update_underscore(t_ast *cmd, char **envv[]);
char	*create_full_var(char *key, char *value);
void	update_var(int index, char *key, char *val, char *envv[]);
int		search_for_key(char *key, char **arr);
int		check_valid_identifier(char *str);

int		is_builtin(t_ast *exec_block, t_uint cmd_count);
int		exec_builtin(t_ast *exec_block, char **envv[]);

void	update_pwd(char *envv[]);
void	update_old_pwd(char **envv[]);

int		exec_echo(t_ast *cmd, char **envv[]);
int		exec_cd(t_ast *cmd, char **envv[]);
int		exec_pwd(t_ast *cmd, char **envv[]);
int		exec_env(t_ast *cmd, char **envv[]);
int		exec_unset(t_ast *cmd, char **envv[]);

int		exec_export(t_ast *cmd, char **envv[]);
void	print_export_list(char *envv[]);
void	print_with_quotes(char *str);

int		exec_exit(t_ast *cmd);

void	print_envp(char **envp); //delete!!!!

#endif
