NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INCDIR) -Ilibft/include

SRCDIR = src/
INCDIR = include

SRC = $(SRCDIR)main.c \
		$(SRCDIR)utils/ft_malloc.c\
		$(SRCDIR)utils/token_utils.c\
		$(SRCDIR)utils/utils.c\
		$(SRCDIR)exec/executor.c\
		$(SRCDIR)exec/exec_minishell.c\
		$(SRCDIR)exec/convert_argv.c\
		$(SRCDIR)exec/exec_external.c\
		$(SRCDIR)exec/exec_redirs.c\
		$(SRCDIR)exec/heredoc.c\
		$(SRCDIR)builtins/builtins.c\
		$(SRCDIR)builtins/cd.c\
		$(SRCDIR)builtins/echo.c\
		$(SRCDIR)builtins/env.c\
		$(SRCDIR)builtins/exit.c\
		$(SRCDIR)builtins/export.c\
		$(SRCDIR)builtins/pwd.c\
		$(SRCDIR)builtins/unset.c\
		$(SRCDIR)parser/parser.c\
		$(SRCDIR)parser/parser_validator.c\
		$(SRCDIR)lexer/lexer_validator.c\
		$(SRCDIR)lexer/lexer.c\
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