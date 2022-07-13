/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:36:49 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/13 11:29:08 by jhille        ########   odam.nl         */
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
	ENV_V,
	EXIT_STAT,
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
int		ft_isalnum(int c);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);

void	free_array(void **ptr_array, const int array_len);

#endif
