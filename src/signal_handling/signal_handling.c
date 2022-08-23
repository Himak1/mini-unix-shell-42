/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 11:33:51 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/23 14:01:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "signal_handling.h"

extern int	g_signal;

void	prompt_interrupt(int num)
{
	if (num)
		g_signal = 1;
}

void	prompt_fresh(void)
{
	write(1, "\n", 1);
	g_signal = 0;
}
