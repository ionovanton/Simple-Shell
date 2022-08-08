NAME				=	minishell

CFLAGS				=	-g -Wall -Wextra -Werror

LIBFT				=	libft/libft.a

LIB					= 	-L/usr/include -lreadline \
						-I${HOME}/.brew/opt/readline/include \
						-L${HOME}/.brew/opt/readline/lib

SOURCE_LIST			=	minishell.c init.c free.c pattern.c sh_exit.c \
						lexer.c lexer_error.c lexer_quote.c lexer_token.c lexer_word.c \
						utils_lexer_1.c utils_lexer_2.c utils_lexer_3.c utils_lexer_4.c \
						parser_1.c parser_2.c \
						utils_parser_1.c utils_parser_2.c utils_parser_3.c utils_parser_4.c \
						utils_node.c \
						utils_pattern.c \
						dict_1.c dict_2.c \
						signals.c \
						check_env.c \
						check_env_2.c

PIPEX				=	pipex.c forker.c redirect.c here_doc.c executor.c 

BUILTINS			=	builtin.c echo.c pwd.c cd.c env.c exit.c utils.c export.c export_utils.c export_add.c unset.c env_struct.c env_struct_utils.c

VPATH				=	builtins/ pipex/ utils/

SRCS				=	$(SOURCE_LIST) $(PIPEX_SRCS) $(BUILTINS_SRCS)

OBJECT_DIRECTORY	:=	objs
OBJECT_LIST			=	$(SOURCE_LIST:.c=.o) $(PIPEX:.c=.o) $(BUILTINS:.c=.o)
OBJS				:=	$(addprefix $(OBJECT_DIRECTORY)/,$(OBJECT_LIST))

HEADER_LIST			=	minishell.h typedef.h pipex.h builtin.h define.h
HDRS				=	$(addprefix includes/,$(HEADER_LIST))

INCLUDE				=	-I includes/ -I libft/ -I ${HOME}/.brew/opt/readline/include -I /usr/local/opt/readline/include

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -lm $(INCLUDE) $(CFLAGS) $(OBJS) $(LIBFT) $(LIB) -o $@
	chmod 777 $(NAME)

$(OBJECT_DIRECTORY)/%.o: %.c $(HDRS) | $(OBJECT_DIRECTORY)
	$(CC) $(CFLAGS) $(INCLUDE) -I libft/ -c $< -o $@

$(OBJECT_DIRECTORY) : 
	mkdir -p $@

$(LIBFT): libft ;

libft:
	$(MAKE) -C libft/

clean:
	$(MAKE) -C libft/ clean
	rm -rfd $(OBJECT_DIRECTORY)
	rm -rf minishell_debug *.dSYM vgcore.*

fclean: clean
	$(MAKE) -C libft/ fclean
	rm -rf $(NAME)

re: cls fclean all

cls:
	printf "\33c\e[3J"

n:
	norminette $(SRCS) includes libft

.PHONY: all run clean fclean re n cls libft