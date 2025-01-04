# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 12:58:07 by ipersids          #+#    #+#              #
#    Updated: 2025/01/04 18:23:06 by ipersids         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    RM = del /q
    RM_DIR = rmdir /s /q
    LIB_EXT = .lib
else
    RM = rm -f
    RM_DIR = rm -rf
    LIB_EXT = .a
endif

# Program name
NAME			:= so_long

# Submodule MLX42
SUBM_MLX_DIR	:= MLX42

# Submodule libft
SUBM_LIBFT_DIR	:= libft
SUBM_LIBFT_LIB	:= $(SUBM_LIBFT_DIR)/libft$(LIB_EXT)

# Compilation variables
CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror
HDRS			:= -Iinclude -I$(SUBM_MLX_DIR)/include -I$(SUBM_LIBFT_DIR)/include
LIBS			:= -L$(SUBM_MLX_DIR)/build -lmlx42 \
				   -L$(SUBM_LIBFT_DIR) -lft \
				   -ldl -lglfw

# Sources and objects
SRCS			:= src/check/path_check.c src/check/dfs_algorithm.c \
				   src/check/map_check.c src/check/map_read.c \
				   src/check/level_check.c \
				   \
				   src/draw/background.c src/draw/image.c src/draw/layout.c \
				   src/draw/animation_coin.c src/draw/image_array.c \
				   src/draw/animation_counter.c src/draw/sprite.c \
				   src/draw/screen.c \
				   \
				   src/initiation/structure_init.c src/initiation/window_init.c \
				   src/initiation/enemy_init.c \
				   \
				   src/hook/hook_close.c src/hook/hook_move.c \
				   src/hook/hook_anim_coin.c src/hook/hook_anim_counter.c \
				   src/hook/hook_game_state.c src/hook/hook.c \
				   \
				   src/error/error.c src/error/memory.c \
				   \
				   src/enemy/enemy_set.c src/enemy/animation_enemy.c \
				   src/enemy/hook_anim_enemy.c \
				   \

SRC_MAIN		:= src/main.c
OBJS			:= $(SRCS:%.c=%.o)
OBJ_MAIN		:= $(SRC_MAIN:%.c=%.o)

# RULES
all: update-submodule build-submodule $(NAME)

$(NAME): $(OBJS) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJS) $(OBJ_MAIN) $(HDRS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HDRS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJ_MAIN)
	$(MAKE) -C $(SUBM_LIBFT_DIR) clean

fclean: clean
	$(RM_DIR) MLX42/build 
	$(RM) $(NAME)
	$(MAKE) -C $(SUBM_LIBFT_DIR) fclean

re: fclean all

# Rule: update submodule MLX42 --init
update-submodule:
	git submodule init
	git submodule update --recursive

# Rule: build Submodule MLX42
build-submodule:
	cd $(SUBM_MLX_DIR) && cmake -B build && cmake --build build -j4
	@echo "\nMLX42 is ready.\n"
	$(MAKE) -C $(SUBM_LIBFT_DIR) 

.PHONY: all clean fclean re update-submodule build-submodule