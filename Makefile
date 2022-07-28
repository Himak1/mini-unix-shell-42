
NAME = minishell

VPATH = src:\
		src/lexer:\
		src/parser:\
		src/expander:\
		src/utils

OBJ = $(addprefix obj/, $(SRC_FILES:.c=.o))

SRC_FILES = $(UTILS_FILES)\
				$(LEXER_FILES)\
				$(PARSER_FILES)\
				$(EXPANDER_FILES)

LEXER_FILES = lexer.c\
				split_command_line.c

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
				lst_new.c\
				xmalloc.c\
				ft_strnstr.c

PARSER_FILES = cmd.c\
				node_functions.c\
				parser.c\
				redirect.c\
				utility_functions.c

EXPANDER_FILES = expander.c\
					utils.c

INC = -Iinclude
CFLAGS = -Wextra -Wall -Werror $(INC) -g

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

obj/%.o: %.c
		@mkdir -p obj
		$(CC) -c $(CFLAGS) -o $@ $^

clean:
		rm -rf obj

fclean: clean
		rm -rf $(NAME)

re: fclean all
