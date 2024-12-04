# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 12:58:07 by ipersids          #+#    #+#              #
#    Updated: 2024/12/04 15:43:21 by ipersids         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME			:= so_long

# Submodule MLX42
SUBMODULE_DIR	:= MLX42

# Compilation variables
CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror
HDRS			:= -Iinclude -I$(SUBMODULE_DIR)/include
LIBS			:= -L$(SUBMODULE_DIR)/build -lmlx42 -ldl -lglfw #-lm

# Sources and objects
SRCS			:= src/input_handler.c src/write.c 
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

fclean: clean
	rm -rf MLX42/build $(NAME)

re: fclean all

# Rule: update submodule MLX42
update-submodule:
	git submodule update --init --recursive

# Rule: build Submodule MLX42
build-submodule:
	cd $(SUBMODULE_DIR) && cmake -B build && cmake --build build -j4
	@echo "\nMLX42 is ready.\n"

# TESTING
TEST_NAME		:= test_main
TEST_SRCS		:= test/test_main.c
TEST_OBJS		:= $(TEST_SRCS:%.c=%.o)

test: $(TEST_NAME)

$(TEST_NAME): $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -g $(TEST_OBJS) $(OBJS) $(HDRS) $(LIBS) -o $(TEST_NAME)

tclean: clean
	rm -f $(TEST_NAME) $(TEST_OBJS)



.PHONY: all clean fclean re update-submodule build-submodule