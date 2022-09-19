
NAME = minishell

VPATH = src:\
		src/lexer:\
		src/parser:\
		src/heredoc:\
		src/expander:\
		src/executor:\
		src/builtins:\
		src/signal_handling:\
		src/utils

OBJ = $(addprefix obj/, $(SRC_FILES:.c=.o))
LIBFT = libft/libft.a

SRC_FILES = main.c\
			$(UTILS_FILES)\
			$(LEXER_FILES)\
			$(PARSER_FILES)\
			$(HEREDOC_FILES)\
			$(EXPANDER_FILES)\
			$(BUILTINS_FILES)\
			$(EXECUTOR_FILES)\
			$(SIGNAL_HANDLING_FILES)

LEXER_FILES = lexer.c\
				split_command_line.c

BUILTINS_FILES = env.c\
					echo.c\
					pwd.c\
					cd.c\
					export.c\
					unset.c\
					environment.c\
					builtins.c\
					builtins_utils.c

UTILS_FILES = lst_new.c\
				lst_add_ft.c\
				lst_add_bk.c\
				lst_clear.c\
				ft_lstfree.c\
				ft_free_2d_array.c\
				lst_new.c\
				ft_xmalloc.c\
				cpy_2d.c\
				ft_get_index_2d.c

PARSER_FILES = cmd.c\
				node_functions.c\
				parser.c\
				redirect.c\
				utility_functions.c

HEREDOC_FILES = heredoc.c\
				file_handling.c\
				read_write_to_tmp.c

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

SIGNAL_HANDLING_FILES = signal_handling.c

READLINE_PATH = vendor/readline
READLINE_LINK = -L vendor/readline/lib -l readline -l ncurses

INC = -Ilibft -Iinclude -I$(READLINE_PATH)/include

ifdef DEBUG
 CFLAGS = -Wextra -Wall -Werror -fsanitize=address -g
 LIBFT_MAKE = make debug -sC libft
else
 CFLAGS = -Wextra -Wall -Werror -g
 LIBFT_MAKE = make -sC libft
endif

all: readline $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) $(INC) -o $@ $^ $(READLINE_LINK)

debug:
	$(MAKE) DEBUG=1 all

obj/%.o: %.c
		@mkdir -p obj
		$(CC) $(CFLAGS) $(INC) -c -o $@ $^

readline: $(READLINE_PATH)

$(READLINE_PATH):
		@mkdir -p vendor
		sh ./install_readline.sh

$(LIBFT): 
		$(LIBFT_MAKE)
		make clean -sC libft

clean:
		rm -rf obj
		make fclean -C libft

fclean: clean
		rm -rf vendor
		rm -rf $(NAME)

re: fclean all

PHONY: make re all clean fclean
