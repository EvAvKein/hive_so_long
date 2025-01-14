# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/01/14 22:22:27 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CHECKER_NAME = checker_ekeinan
BONUS_NAME = .bonus

LIBFT_DIR = libft_full
LIBFT_LIB = $(LIBFT_DIR)/libft_full.a

MLX_DIR = MLX42
MLX_BUILD_DIR = build
MLX_LIB = $(MLX_DIR)/$(MLX_BUILD_DIR)/libmlx42.a

SRC_DIR = src
SRC_FILES = main.c \
		 	errors.c \
	 		free.c \
			utils.c \
			math.c \
	  		adjacent.c \
	  		map/save_map.c \
	  		map/validate_map_contents.c \
	  		map/validate_map_path.c \
			mlx/images.c \
			mlx/render.c \
			mlx/hooks.c
	  

COMPILE_FLAGS = -Wall -Wextra -Werror
COMPILE_WITH_MLX = $(MLX_LIB) -Iinclude -ldl -lglfw -pthread -lm

OBJ = $(SRC_FILES:%.c=$(SRC_DIR)/%.o)

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
