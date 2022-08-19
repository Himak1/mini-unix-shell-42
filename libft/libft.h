/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 18:27:55 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/18 16:05:48 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *_new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *_new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void*));
t_list				*ft_lstmap(t_list *lst,
						void *(*f)(void*), void (*del)(void*));

int					ft_atoi(const char *nptr);
void				*ft_bzero(void *dest, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_resetptr(void **ptr);
void				ft_free_2d(void *two_d_array[]);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);

void				*ft_memccpy(void *dest,
						const void *source, int c, size_t num);
void				*ft_memchr(const void *src, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memcpy(void *dest, const void *source, size_t num);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *dest, int val, size_t len);
char				*ft_strchr(const char *str, int c);

char				*ft_strdup(const char *str);
size_t				ft_strlcat(char *dest, const char *src, size_t destsize);
size_t				ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
char				*ft_strrchr(const char *str, int c);

int					ft_tolower(int c);
int					ft_toupper(int c);

char				*ft_substr(char const *str, unsigned int start, size_t len);
char				*ft_strjoin(char const *str1, char const *str2);
char				*ft_strtrim(char const *str, char const *rm);
char				**ft_split(char const *str, char c);
char				*ft_itoa(int n);
char				*ft_uitoa(unsigned int n);
char				*ft_strmapi(char const *str, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
void				ft_putendl_fd(char *str, int fd);
void				ft_putnbr_fd(int n, int fd);

int					ft_printf(const char *format, ...);
#endif
