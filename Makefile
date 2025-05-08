NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INCDIR) -Ilibft/include

SRCDIR = src/
INCDIR = include

SRC = $(SRCDIR)main.c \
		$(SRCDIR)utils/environ.c\
		$(SRCDIR)utils/error.c\
		$(SRCDIR)utils/ft_malloc.c\
		$(SRCDIR)utils/helpers.c\
		$(SRCDIR)utils/token_list.c\
		$(SRCDIR)parser/parser_utils.c\
		$(SRCDIR)parser/parser.c\
		$(SRCDIR)parser/token_utils.c\
		$(SRCDIR)lexer/lexer_utils.c\
		$(SRCDIR)lexer/lexer.c\
		$(SRCDIR)lexer/word_handler.c\
		$(SRCDIR)redirect/heredoc.c\
		$(SRCDIR)executor/executor.c\
		$(SRCDIR)executor/execute_command.c\
		$(SRCDIR)executor/execute_pipe.c\
		$(SRCDIR)executor/execute_redirect.c\
		$(SRCDIR)builtin/builtins.c\
		$(SRCDIR)builtin/cd.c\
		$(SRCDIR)builtin/echo.c\
		$(SRCDIR)builtin/env.c\
		$(SRCDIR)builtin/exit.c\
		$(SRCDIR)builtin/export.c\
		$(SRCDIR)builtin/export_print.c\
		$(SRCDIR)builtin/pwd.c\
		$(SRCDIR)builtin/unset.c\
		$(SRCDIR)signals/signals.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	@rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re