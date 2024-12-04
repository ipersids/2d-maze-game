# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 12:58:07 by ipersids          #+#    #+#              #
#    Updated: 2024/12/04 19:21:58 by ipersids         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME			:= so_long

# Submodule MLX42
SUBM_MLX_DIR	:= MLX42

# Submodule ft_printf
SUBM_PRINT_DIR	:= ft-printf
SUBM_PRINT_LIB	:= $(SUBM_PRINT_DIR)/libftprintf.a

# Compilation variables
CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror
HDRS			:= -Iinclude -I$(SUBM_MLX_DIR)/include -I$(SUBM_PRINT_DIR)
LIBS			:= -L$(SUBM_MLX_DIR)/build -lmlx42 \
				   -L$(SUBM_PRINT_DIR) -lftprintf \
				   -ldl -lglfw #-lm

# Sources and objects
SRCS			:= src/input_handler.c
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
	rm -f $(OBJS) $(OBJ_MAIN)
	$(MAKE) -C $(SUBM_PRINT_DIR) clean

fclean: clean
	rm -rf MLX42/build $(NAME)
	$(MAKE) -C $(SUBM_PRINT_DIR) fclean

re: fclean all

# Rule: update submodule MLX42
update-submodule:
	git submodule update --init --recursive

# Rule: build Submodule MLX42
build-submodule:
	cd $(SUBM_MLX_DIR) && cmake -B build && cmake --build build -j4
	@echo "\nMLX42 is ready.\n"
	$(MAKE) -C $(SUBM_PRINT_DIR) 

# TESTING
TEST_NAME		:= test_main
TEST_SRCS		:= test/test_main.c
TEST_OBJS		:= $(TEST_SRCS:%.c=%.o)

test: update-submodule build-submodule $(TEST_NAME)

$(TEST_NAME): $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -g $(TEST_OBJS) $(OBJS) $(HDRS) $(LIBS) -o $(TEST_NAME)

tclean: clean
	rm -f $(TEST_NAME) $(TEST_OBJS)



.PHONY: all clean fclean re update-submodule build-submodule