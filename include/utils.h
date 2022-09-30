/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:36:49 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/30 15:59:17 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef unsigned int	t_uint;

enum e_types
{
	WORD,
	RDR_IN,
	RDR_OUT,
	RDR_DLM_IN,
	RDR_APND_OUT,
	PIPE,
	SIG_INT,
	SIG_EOF
};

typedef struct s_token
{
	t_uint			type;
	char			*value;
	struct s_token	*next;
}					t_token;

t_token	*lst_new(t_uint type, char *value);
void	lst_add_bk(t_token **list, t_token *node);
void	lst_add_ft(t_token **list, t_token *node);
void	lst_clear(t_token *list);

void	*ft_xmalloc(size_t bytes);
char	**ft_free_2d_array(char **arr);
void	ft_lstfree(t_token *tokenlist);
void	free_array(void **ptr_array, const int array_len);
int		ft_get_index_key(char **str_arr, char *str);
int		ft_get_index(char **str_arr, char *str);
char	*ft_getenv(char **envv, char *var_name);
char	**cpy_2d(char **arr);
char	**sort_2d_alpha(char *arr[], int size);

char	**ft_xsplit(char *str, char delim);
char	*ft_xstrdup(char *str);
char	*ft_xstrjoin(char *str1, char *str2);

#endif
