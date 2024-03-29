/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 17:02:16 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/30 16:03:17 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "builtins.h"
#include "signal_handling.h"

static int	search_shlvl(char *envv[])
{
	int	i;

	i = 0;
	while (envv[i])
	{
		if (!ft_strncmp(envv[i], "SHLVL=", 6))
			return (i);
		i++;
	}
	return (-1);
}

void	increase_shlvl(char *envv[])
{
	int		shlvl;
	int		index;
	char	*new_shlvl;
	char	**key_and_val;

	index = search_shlvl(envv);
	key_and_val = ft_xsplit(envv[index], '=');
	shlvl = ft_atoi(key_and_val[1]);
	new_shlvl = ft_itoa(shlvl + 1);
	if (!new_shlvl)
		exit(EXIT_FAILURE);
	free(envv[index]);
	envv[index] = create_full_var("SHLVL", new_shlvl);
	ft_free_2d_array(key_and_val);
	free(new_shlvl);
}

void	set_termios(t_data *data)
{
	tcgetattr(STDIN_FILENO, &data->config);
	data->config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->config);
}

void	copy_envp(t_data *data, char *envp[])
{
	t_uint	envp_size;
	t_uint	i;

	i = 0;
	envp_size = 0;
	while (envp[envp_size])
		envp_size++;
	data->envv = ft_xmalloc((envp_size + 1) * sizeof(char *));
	while (envp[i])
	{
		data->envv[i] = ft_xstrdup(envp[i]);
		i++;
	}
	data->envv[i] = NULL;
	increase_shlvl(data->envv);
}

void	shell_init(t_data *data, char *envp[])
{
	copy_envp(data, envp);
	signals_on_init(data);
	set_termios(data);
}
