/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 12:20:45 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/23 13:23:08 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

void	sh_error(void);
void	cmd_error_exit(char *cmd);
void	dir_error_msg(t_ast *cmd);
void	not_valid_identifier_msg(char *str);
#endif