/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 12:20:45 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/23 12:18:46 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H
# define NOT_FOUND 1
# define IS_DIR 2

void	sh_error(void);
void	cmd_error_exit(char *cmd);
void	cmd_custom_exit(char *cmd, int error_type);

#endif
