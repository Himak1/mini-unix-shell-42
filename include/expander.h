/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 11:51:40 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/25 15:21:33 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

char	**create_envp();
char	*remove_quotes(char *value, char quote);
char	**expand_dollar_sign(char *value);//, char **envp);
int		count_dollar_sign(char *value);
char	**get_env_var(char **env_var, char *value, int count);
int		get_env_var_len(char *env_var);//, int i);
#endif