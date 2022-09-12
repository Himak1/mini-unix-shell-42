/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:16:05 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/12 14:01:55 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H
# include <signal.h>

void	prompt_interrupt(int num);
void	prompt_fresh(void);

void	heredoc_interrupt(int num);

#endif
