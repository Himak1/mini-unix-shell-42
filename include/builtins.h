/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 12:43:48 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/17 15:00:17 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct t_env_list	*next;
}						t_env_list;

int		pwd(void);

void	echo(char **arg);
int		check_n(char *arg);
int		et_index_arg(char **arg);

void	print_env(char **envp);

#endif
