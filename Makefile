
NAME = minishell

VPATH = src:\
		src/lexer:\
		src/utils

OBJ = $(addprefix obj/, $(SRC_FILES:.c=.o))

SRC_FILES = main.c\
			$(LEXER_FILES)\
			$(UTILS_FILES)

LEXER_FILES = lexer.c\
				get_type.c

UTILS_FILES = ft_isalnum.c\
				ft_strlen.c\
				ft_strncmp.c\
				ft_substr.c\
				lst_new.c\
				lst_add_ft.c\
				lst_add_bk.c\
				lst_clear.c\
				lst_new.c
INC = -Iinclude
CFLAGS = -Wextra -Wall -Werror $(INC)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -lreadline -o $@ $^

obj/%.o: %.c
		@mkdir -p obj
		$(CC) -c $(CFLAGS) -o $@ $^

clean:
		rm -rf obj

fclean: clean
		rm -rf $(NAME)

re: fclean all
