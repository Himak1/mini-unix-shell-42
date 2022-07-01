/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_type.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 13:25:36 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/01 16:08:07 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_uint	is_env_v(char *value)
{
	size_t	i;

	i = 0;
	if (value[i] != '$')
		return (0);
	i++;
	while (ft_isalnum(value[i]))
		i++;
	if (i != ft_strlen(value))
		return (0);
	return (1);
}

t_uint	get_type(char *value)
{
	t_uint	type;

	if (!ft_strncmp(value, "<", ft_strlen(value)))
		type = RDR_IN;
	else if (!ft_strncmp(value, ">", ft_strlen(value)))
		type = RDR_OUT;
	else if (!ft_strncmp(value, "<<", ft_strlen(value)))
		type = RDR_DLM_IN;
	else if (!ft_strncmp(value, ">>", ft_strlen(value)))
		type = RDR_APND_OUT;
	else if (!ft_strncmp(value, "|", ft_strlen(value)))
		type = PIPE;
	else if (!ft_strncmp(value, "$?", ft_strlen(value)))
		type = EXIT_STAT;
	else if (is_env_v(value))
		type = ENV_V;
	else
		type = WORD;
	return (type);
}
