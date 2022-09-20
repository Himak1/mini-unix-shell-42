/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 17:16:16 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/20 17:23:04 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_INIT_H
# define SHELL_INIT_H
# include "minishell.h"

void    shell_init(t_data *data, char *envp[]);
void	increase_shlvl(char *envv[]);
void	set_termios(t_data *data);
void	copy_envp(t_data *data, char *envp[]);

#endif
