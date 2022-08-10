/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 11:13:58 by jhille        #+#    #+#                 */
/*   Updated: 2021/11/21 23:00:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define MAX_FD 4096
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif
# include <stddef.h>

int		get_next_line(int fd, char **line);

void	ft_setzero(void *dest, size_t n);

int		linelen(char *str, int returntype);

char	*gnl_substr(char *str, unsigned int start, size_t len);

void	*ft_gnl_calloc(size_t nmemb, size_t size);

char	*ft_gnl_strjoin(char *str1, char *str2);
#endif
