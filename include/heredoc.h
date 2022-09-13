/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 11:48:27 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/13 13:20:35 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "parser.h"
# include "minishell.h"

int		handle_all_heredocs(t_data *data);
int		single_heredoc(char *tmp_filepath, t_ast *rd, char *envv[], int i);

char	*find_tmp_filepath(void);
char	*create_tmp_filename(char *tmp_filepath, int i);
void	read_write_to_tmp(char *delimiter, int fd, char *envv[]);

#endif
