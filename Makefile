# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 12:58:07 by ipersids          #+#    #+#              #
#    Updated: 2024/12/27 14:51:56 by ipersids         ###   ########.fr        #
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
				   -ldl -lglfw -lm

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
				   \
				   src/hook/hook_close.c src/hook/hook_move.c \
				   src/hook/hook_anim_coin.c src/hook/hook_anim_counter.c \
				   src/hook/hook_menu.c \
				   \
				   src/error/error.c src/error/memory.c \
				   \

SRC_MAIN		:= main.c
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
	git submodule update --recursive

# Rule: build Submodule MLX42
build-submodule:
	cd $(SUBM_MLX_DIR) && cmake -B build && cmake --build build -j4
	@echo "\nMLX42 is ready.\n"
	$(MAKE) -C $(SUBM_LIBFT_DIR) 

# TESTING
TEST_NAME		:= test_main
TEST_SRCS		:= test/test_main.c
TEST_OBJS		:= $(TEST_SRCS:%.c=%.o)

test: update-submodule build-submodule $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -g $(TEST_OBJS) $(OBJS) $(HDRS) $(LIBS) -o $(TEST_NAME) -I.

tclean: clean
	$(RM) $(TEST_NAME) $(TEST_OBJS)



.PHONY: all clean fclean re update-submodule build-submodule