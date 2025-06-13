# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 12:04:18 by gangel-a          #+#    #+#              #
#    Updated: 2025/06/13 17:46:19 by gangel-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = src/
OBJ_DIR = obj/

SRC = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_free_matrix.c \
		ft_htoi.c \
		ft_itoa.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_num_abs.c \
		ft_printf_fd.c \
		ft_printf.c \
		ft_printunbr.c \
		ft_printf_utils.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_putptr_fd.c \
		ft_putbase_fd.c \
		ft_recalloc.c \
		ft_split.c \
		ft_striteri.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_strdup_split.c \
		ft_strjoin.c \
		ft_strjoin_free.c \
		ft_strrchr.c \
		ft_strtoll_check.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strmapi.c \
		ft_strlen.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_toupper.c \
		ft_tolower.c
BONUS_SRC = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR), $(BONUS_SRC:%.c=%.o))

CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC -I
HEADER = include

# ------------------------------ GNL ------------------------------

GNL_NAME = get_next_line
GNL_DIR = get_next_line/src/
GNL_OBJ_DIR = get_next_line/obj/
GNL_HEADER = get_next_line/include
GNL_SRC = get_next_line.c \
			get_next_line_utils.c
GNL_OBJ = $(addprefix $(GNL_OBJ_DIR), $(GNL_SRC:%.c=%.o))

# ------------------------------ Rules ------------------------------

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@printf "library created\n"

bonus: $(OBJ_DIR) $(BONUS_OBJ)
	@ar rcs $(NAME) $(BONUS_OBJ)
	@printf "bonus created\n"

gnl: $(GNL_OBJ_DIR) $(GNL_OBJ) | $(NAME)
	@if ! ar t $(NAME) | grep -q "get_next_line.o"; then \
		ar rcs $(NAME) $(GNL_OBJ); \
		printf "gnl added\n"; \
	fi

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS)$(HEADER) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@
	@printf "object directory created\n"

$(GNL_OBJ_DIR):
	@mkdir -p $@
	@printf "GNL object directory created\n"

$(GNL_OBJ_DIR)%.o: $(GNL_DIR)%.c
	@$(CC) $(CFLAGS)$(GNL_HEADER) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus gnl