/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 15:28:23 by jhille        #+#    #+#                 */
/*   Updated: 2021/03/28 20:40:42 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft.h"
# define CONVS "cspdiuxX%"
# define FLAGS "-0"

typedef struct s_trct
{
	int			flags;
	int			width;
	int			prec;
	char		conv;
}				t_strct;

int		ft_printf(const char *format, ...);
int		ft_vfprintf(const char *format, va_list args);
int		printlen(const char *str, int i, va_list args, t_strct *list);
int		write_check(char *store, int len, int i);
void	ft_skipchar(const char *format, int *pos);
void	return_check(const char **format, char **store, int *pos, int *i);

void	strctzero(t_strct *ptr);

char	*width_correct(char *ret, char c, int olen, int nlen);
char	*ft_strrealloc(char *ptr, size_t newsize);

int		varcheck(const char *str, int len, va_list args, t_strct *lst);
int		get_width_prec(const char *format, int startnum, int endnum);
int		struct_set(const char *str, int *parameter, int *len);
void	arg_set(const char *str, int *strct_int, int *len, va_list args);
void	flag_set(const char *str, int *len, t_strct *lst);

char	*varjoin(t_strct *lst, va_list args);

char	*char_set(t_strct *lst, va_list args);
char	*str_set(t_strct *lst, va_list args);
char	*ptr_set(t_strct *lst, va_list args);
char	*int_set(t_strct *lst, va_list args);
char	*hexstr_set(t_strct *lst, va_list args);
char	*percent_set(char c, t_strct *lst);
char	*uint_set(t_strct *lst, va_list args);

char	*hex_set(long long convert, int letcase);
#endif
