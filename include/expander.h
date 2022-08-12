/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 11:51:40 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/11 11:08:04 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "utils.h"

typedef struct s_env_var
{
	int					len_env;
	int					len_exp_env;
	char				*env_value;
	char				*exp_env_value;
	struct s_env_var	*next;
}						t_env_var;

char		**create_envp();

//expand_utils
void		check_env_var(t_env_var **env_var_list, char **envp);
char		*find_exp_var(char *env_var, char **envp);
char		*save_exp_val(char *full_env_val, char *alias);
int			get_exp_len(t_env_var *env_var_list, int len_input);
char		*expand_input(char *input, t_env_var *env_var_list, int len);

//env_list_utils
t_env_var	*create_env_var(char *value);
void		create_env_var_list(t_env_var **env_var_list, char **env_var);
void		lst_add_bk_env_var(t_env_var **list, t_env_var *env_var);
char		**get_env_var(char *value);
int			get_env_var_len(char *env_var);

//quote removal
int			len_filtered_quotes(char *value);
void		copy_filtered_quotes(char *new_value, char *old_value, size_t size);
char		*remove_quotes(char *value);

//expander
int			count_dollar_sign(char *value);
char		*expand_dollar_sign(char *input, char **envp);
void		expander(char **input, char **envp);
void		expand_tree(t_ast *parent, char **envp);


#endif