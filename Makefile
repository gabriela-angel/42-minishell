# NAME
NAME = minishell

# LIBS
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libft/

# COMPILATIONS AND FLAGS
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -Iinclude
LIB_PATHS = -L$(LIBFT_DIR) -lft -lreadline

# PATHS
SRC_DIR = src/
BTIN_DIR = src/builtins/
EXC_DIR = src/exec/
EXP_DIR = src/expansion/
HDOC_DIR = src/heredoc/
LXR_DIR = src/lexer/
PRS_DIR = src/parser/
SIG_DIR = src/signals/
UTL_DIR = src/utils/
OBJ_DIR = obj/

# FILES AND OBJECTS
SRC := $(addprefix $(SRC_DIR), main.c) \
		$(addprefix $(BTIN_DIR), builtins.c cd.c echo.c env.c exit.c export.c export_print.c pwd.c unset.c) \
		$(addprefix $(EXC_DIR), executor.c exec_simple.c exec_pipe.c exec_redirs.c exec_external.c convert_argv.c) \
		$(addprefix $(EXP_DIR), expand.c expand_utils.c wildcard.c wildcard_utils.c) \
		$(addprefix $(HDOC_DIR), heredoc.c heredoc_utils.c) \
		$(addprefix $(LXR_DIR), lexer.c lexer_validator.c) \
		$(addprefix $(PRS_DIR), parser.c parser_validator.c) \
		$(addprefix $(SIG_DIR), signals.c) \
		$(addprefix $(UTL_DIR), utils.c exit_and_error.c ft_malloc.c token_utils.c)

OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# VALGRIND
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.supp

# ------------------------------ COLORS ------------------------------

BLUE		=	\033[0;34m
BLUE_BOLD	=	\033[1;34m
GREEN_BOLD	=	\033[1;92m
YELLOW_BOLD	=	\033[1;93m
YELLOW		=	\033[0;33m
RED			=	\033[0;91m
MAGENTA 	=	\033[1;35m
MAGENTA_BOLD = \033[1;35m
CYAN		=	\033[0;96m
CYAN_BOLD	=	\033[1;36m
RESET		=	\033[0m

# ------------------------------ RULES ------------------------------

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory
	@printf "$(GREEN_BOLD)Libft compiled.$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(BLUE)$@: $(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN_BOLD)Object compiled.$(RESET)\n"

$(NAME): $(OBJ) $(LIBFT)
	@printf "$(GREEN_BOLD) => 100%%$(RESET)\n"
	@printf "$(MAGENTA_BOLD)[minishell]:\t$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIB_PATHS) -o $@
	@printf "$(GREEN_BOLD) => Success!$(RESET)\n"

norm:
	@echo "\n$(CYAN_BOLD)======= LIBFT =======$(RESET)"
	@norminette libft | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(YELLOW_BOLD)======= MANDATORY =======$(RESET)"
	@norminette src | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(MAGENTA_BOLD)======= INCLUDES =======$(RESET)"
	@norminette include | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'
	@echo "\n"

val: re
	@$(VALGRIND) ./$(NAME)

clean:
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR)
	@printf "$(MAGENTA_BOLD)[minishell]:\tobject files$(RESET)$(GREEN_BOLD)  => Cleaned!$(RESET)\n"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)
	@printf "$(MAGENTA_BOLD)[LIBFT]:\texec. files$(RESET)$(GREEN_BOLD) => Cleaned!$(RESET)\n"
	@printf "$(MAGENTA_BOLD)[minishell]:\texec. files$(RESET)$(GREEN_BOLD)  => Cleaned!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re norm