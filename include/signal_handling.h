/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:16:05 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/19 15:52:50 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H
# include <signal.h>
# include "minishell.h"

void	signals_on_init(t_data *data);
void	init_sigaction(struct sigaction *sa, void (*handler)(int));

void	prompt_interrupt(int num);
void	heredoc_interrupt(int num);

#endif
