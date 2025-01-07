# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/01/03 18:43:57 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CHECKER_NAME = checker_ekeinan
BONUS_NAME = .bonus

LIBFT_DIR = libft_full
LIBFT_LIB = $(LIBFT_DIR)/libft_full.a

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/libmlx42.a

INCLUDE = so_long.h \
		  errors.h

SRC = main.c \
	  errors.c \
	  validate.map.c
	  

COMPILE_FLAGS = -Wall -Wextra -Werror
COMPILE_WITH_MLX = libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s --no-print-directory

$(MLX_LIB):
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	cc $(COMPILE_FLAGS) $(OBJ) $(LIBFT_LIB) $(COMPILE_WITH_MLX) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(CHECKER_NAME) $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	rm -f $(NAME) tags

re: fclean all

neat: $(NAME) clean
	ctags -R *
	clear

.PHONY: all bonus clean fclean re
