/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:16:05 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/13 11:08:30 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H
# include <signal.h>

void	init_sigaction(struct sigaction *sa, void (*handler)(int));

void	prompt_interrupt(int num);
void	heredoc_interrupt(int num);

#endif
