/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:36:49 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/01 14:42:21 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>

typedef unsigned int	t_uint;

enum e_types
{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	
};

typedef struct s_token
{
	t_uint			type;
	char			*value;
	struct s_token	*next;
}				t_token;

t_token	*lst_new(t_uint type, char *value);
void	lst_add_bk(t_token **list, t_token *node);
void	lst_add_ft(t_token **list, t_token *node);
void	lst_clear(t_token **list);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

#endif
