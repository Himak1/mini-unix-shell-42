
NAME = minishell

VPATH = src:\
		src/lexer:\
		src/builtins:\
		src/utils

OBJ = $(addprefix obj/, $(SRC_FILES:.c=.o))

SRC_FILES = main.c\
			$(UTILS_FILES)\
			$(LEXER_FILES)\
			$(BUILTINS_FILES)
			

LEXER_FILES = lexer.c\
				split_command_line.c

BUILTINS_FILES = pwd.c

UTILS_FILES = ft_strlen.c\
				ft_strncmp.c\
				lst_new.c\
				lst_add_ft.c\
				lst_add_bk.c\
				lst_clear.c\
				ft_lstfree.c\
				ft_strlcpy.c\
				ft_strdup.c\
				ft_free_2d_array.c\
				lst_new.c

INC = -Iinclude
CFLAGS = -Wextra -Wall -Werror $(INC) -g

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

PHONY: make re all clean fclean
