# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/02/05 11:52:39 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

LIBFT_DIR := libft_full
LIBFT_LIB := $(LIBFT_DIR)/libft_full.a

MLX_REPO := https://github.com/codam-coding-college/MLX42.git
MLX_DIR := MLX42
MLX_BUILD_DIR := build
MLX_LIB := $(MLX_DIR)/$(MLX_BUILD_DIR)/libmlx42.a

SRC_DIR := src
SRC_FILES := main.c \
			player.c \
			foes.c \
			adjacent.c \
			utils.c \
		 	perrs.c \
	 		exit.c \
	  		map/save_map.c \
	  		map/validate_map_contents.c \
	  		map/validate_map_path.c \
	  		map/visualize.c \
			mlx/images_init.c \
			mlx/images_utils.c \
			mlx/update_overlayed.c

INCLUDE_DIR := include
INCLUDE_FILES := so_long.h \
				 structs.h \
				 perrs.h \
				 settings.h

CC := clang
COMPILE_FLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR)
COMPILE_WITH_MLX := $(MLX_LIB) -Iinclude -ldl -lglfw -pthread -lm

OBJ := $(SRC_FILES:%.c=$(SRC_DIR)/%.o)
HEADERS := $(INCLUDE_FILES:%=$(INCLUDE_DIR)/%)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s --no-print-directory

$(MLX_LIB):
	if ! find . | grep MLX42; then \
		git clone $(MLX_REPO) $(MLX_DIR);\
	fi;
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

%.o: %.c
	$(CC) $(COMPILE_FLAGS) -c $< -o $@ -D VISUALIZE=$(if $(VISUALIZE),1,0)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ) $(HEADERS)
	$(CC) $(COMPILE_FLAGS) $(OBJ) $(LIBFT_LIB) $(COMPILE_WITH_MLX) -o $(NAME)

visualize: export VISUALIZE = 1
visualize: $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	@$(MAKE) $(NAME) --no-print-directory

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	rm -rf $(NAME) $(MLX_DIR)

re: fclean all

neat: $(NAME) clean
	clear

.PHONY: all visualize bonus clean fclean re neat
