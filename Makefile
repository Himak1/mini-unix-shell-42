
NAME = minishell

VPATH = src:\
		src/lexer:\
		src/parser:\
		src/expander:\
		src/executor:\
		src/builtins:\
		src/utils

OBJ = $(addprefix obj/, $(SRC_FILES:.c=.o))
LIBFT = libft/libft.a

SRC_FILES = main.c\
			$(UTILS_FILES)\
			$(LEXER_FILES)\
			$(PARSER_FILES)\
			$(EXPANDER_FILES)\
			$(BUILTINS_FILES)\
			$(EXECUTOR_FILES)
			

LEXER_FILES = lexer.c\
				split_command_line.c

BUILTINS_FILES = pwd.c

UTILS_FILES = lst_new.c\
				lst_add_ft.c\
				lst_add_bk.c\
				lst_clear.c\
				ft_lstfree.c\
				ft_free_2d_array.c\
				lst_new.c\
				xmalloc.c\

PARSER_FILES = cmd.c\
				node_functions.c\
				parser.c\
				redirect.c\
				utility_functions.c

EXPANDER_FILES = expander.c\
					expand_utils.c\
					env_var_utils.c\
					remove_quotes.c

EXECUTOR_FILES = executor.c\
					handle_redirects.c\
					handle_pipes.c\
					extract_ast_data.c\
					getcmd.c\
					add_cmd_path.c\
					getfd.c

INC = -Ilibft -Iinclude

ifdef DEBUG
 CFLAGS = -Wextra -Wall -Werror -fsanitize=address -g
 LIBFT_MAKE = make debug -sC libft
else
 CFLAGS = -Wextra -Wall -Werror
 LIBFT_MAKE = make -sC libft
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS) $(INC) -lreadline -o $@ $^

debug:
	$(MAKE) DEBUG=1 all

obj/%.o: %.c
		@mkdir -p obj
		$(CC) $(CFLAGS) $(INC) -c -o $@ $^

$(LIBFT): 
		$(LIBFT_MAKE)
		make clean -sC libft

clean:
		rm -rf obj
		make fclean -C libft

fclean: clean
		rm -rf $(NAME)

re: fclean all

PHONY: make re all clean fclean
