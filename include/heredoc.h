/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 11:48:27 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/19 11:57:59 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "parser.h"

void	handle_all_heredocs(t_ast *exec_block, char *envv[]);
void	single_heredoc(char *tmp_filepath, t_ast *rd, char *envv[], int i);

char	*find_tmp_filepath(void);
char	*create_tmp_filename(char *tmp_filepath, int i);
void	read_write_to_tmp(char *delimiter, int fd, char *envv[]);

#endif
