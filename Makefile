# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 12:58:07 by ipersids          #+#    #+#              #
#    Updated: 2024/12/03 18:11:32 by ipersids         ###   ########.fr        #
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
LIBS			:= -L$(SUBMODULE_DIR)/build -lmlx42

# RULES
# all:

# clean:

# fclean:

# re: fclean all

# Rule: update submodule MLX42
update-submodule:
	git submodule update --init --recursive

# Rule: build Submodule MLX42
build-submodule:
	cd $(SUBMODULE_DIR) && cmake -B build && cmake --build build -j4