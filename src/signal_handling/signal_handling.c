/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 11:33:51 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/23 13:10:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handling.h"

extern int	g_signal;

void	prompt_reset(int num)
{
	if (num)
		g_signal = 1;
}
