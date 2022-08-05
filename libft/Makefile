# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jhille <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/29 16:15:51 by jhille        #+#    #+#                  #
#    Updated: 2022/08/05 15:00:36 by jhille        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

REG_FILES = ft_atoi.c\
		    ft_bzero.c\
		   	ft_calloc.c\
		   	ft_isalnum.c\
		   	ft_isascii.c\
			ft_isalpha.c\
		   	ft_isdigit.c\
		   	ft_isprint.c\
			ft_itoa.c\
			ft_uitoa.c\
		   	ft_memccpy.c\
		   	ft_memcpy.c\
		   	ft_memchr.c\
		   	ft_memcmp.c\
			ft_memmove.c\
		   	ft_memset.c\
		   	ft_putchar_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
		   	ft_putstr_fd.c\
		   	ft_split.c\
		   	ft_strchr.c\
		   	ft_strdup.c\
			ft_strjoin.c\
			ft_strlcat.c\
		   	ft_strlcpy.c\
		   	ft_strlen.c\
		   	ft_strmapi.c\
		   	ft_strncmp.c\
		   	ft_strnstr.c\
		   	ft_strrchr.c\
		   	ft_strtrim.c\
		   	ft_substr.c\
		   	ft_tolower.c\
		   	ft_toupper.c\
			ft_resetptr.c\
			ft_striteri.c\
			ft_free_2d.c

GNL_SRC = get_next_line_bonus.c\
			get_next_line_utils_bonus.c

FT_PRINTF_SRC = ft_printf.c\
				ft_varcheck.c\
				int_set.c\
				return_check.c\
				write_check.c\
				hex_set.c\
				basic_sets.c\
				printf_utils.c\
				varcheck_states.c

BONUS_FILES = ft_lstadd_back.c\
			  ft_lstadd_front.c\
			  ft_lstclear.c\
			  ft_lstdelone.c\
			  ft_lstiter.c\
			  ft_lstlast.c\
			  ft_lstmap.c\
			  ft_lstnew.c\
			  ft_lstsize.c

VPATH = ft_printf:\
		gnl

REG_OBJ_FILES = $(REG_FILES:.c=.o)\
				$(GNL_SRC:.c=.o)\
				$(FT_PRINTF_SRC:.c=.o)

BONUS_OBJ_FILES = $(BONUS_FILES:.c=.o)

ifdef WITH_BONUS
 OBJ = $(addprefix obj/, $(REG_OBJ_FILES) $(BONUS_OBJ_FILES))
else
 OBJ = $(addprefix obj/, $(REG_OBJ_FILES))
endif

CFLAGS = -Wextra -Wall -Werror

all: $(NAME)

$(NAME): $(OBJ)
		ar -cr $@ $^

obj/%.o: %.c
		@mkdir -p obj
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus:
	$(MAKE) WITH_BONUS=1 all

.PHONY: all clean fclean re bonus
