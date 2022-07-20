/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:36:49 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/20 14:42:55 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

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
void	lst_clear(t_token **list);

void	*xmalloc(size_t bytes);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_free_2d_array(char **arr);
void	ft_lstfree(t_token *tokenlist);
char	*ft_strdup(const char *str);

void	free_array(void **ptr_array, const int array_len);

#endif
