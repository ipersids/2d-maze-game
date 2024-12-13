/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:52:27 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/13 23:57:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** 
 * 	@todo small things:
 *  1) 	dfs_algorithm.c -> dfs()
 * 		Add termination when all items are visited. 
 * 		Check "is_move_safe" separately.
 * 	2)	error.c -> create an enum for error codes and a function to get error 
 * 		messages from a list using code (mlx42 as reference).
 * 	3)	map_check.c -> move some checks to private.
 * 	4)	Add a final map check: if the map fits the maximum monitor size.
 */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <fcntl.h>			// open
# include <stdio.h>			// perror
# include <string.h>		// strerror
// # include <math.h>			// math library

# include "libft.h"			// libft library

# ifndef WIDTH
#  define WIDTH 1366
# endif

# ifndef HEIGHT
#  define HEIGHT 768
# endif

# ifndef SPRITE_SIZE
#  define SPRITE_SIZE 64
# endif

# define NAME "So loooooooooooong game!"
# define EXTENSION ".ber"

/**
 * @brief Map decoder
 * 
 * - MAP_CODE[0] = '0' (empty)  
 * 
 * - MAP_CODE[1] = '1' (wall)
 * 
 * - MAP_CODE[2] = 'C' (collectible)
 * 
 * - MAP_CODE[3] = 'E' (exit)  
 * 
 * - MAP_CODE[4] = 'P' (player)
 * 
 */
# define MAP_CODE "01CEP"

/**
 * @note Colors for ft_printf
 */

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define DEFAULT "\033[0m"

/**
 * @brief Structure representing a map with its elements.
 * 
 * `item` - Total number of collectibles on the map.
 * `row` - Number of rows in the map (y-axis).
 * `col` - Number of columns in the map (x-axis).
 * `player[3]` - {amount, x, y}.
 * `exit[3]` - {amount, x, y}.
 * `map_arr` - 2D array representing the map, with dimensions `[row][col]` 
 * 			   where each element stores a character value representing 
 * 			   the map's content.
 */
typedef struct s_map
{
	size_t	item;
	size_t	row;
	size_t	col;
	size_t	player;
	size_t	p_xy[2];
	size_t	exit;
	size_t	e_xy[2];
	char	**map_arr;
}			t_map;

// typedef struct s_game
// {
// 	t_map	*map;
// }			t_game;

void	input_esc_hook(void *param);
void	input_move_hook(mlx_key_data_t keydata, void *param);
char	**so_read_map(int fd);

/* ---------------------------- Validate Input ----------------------------- */

void	so_validate_everything(int argc, char **argv, t_map *map);
int		is_args_valid(int argc, char **argv);
int		is_line_valid(t_map *map, size_t y);
int		is_map_valid(t_map *map);
int		is_map_playable(t_map *map);

/* ---------------------------- Error Handling ----------------------------- */

void	so_exit_error(const char *message, int exit_code);
void	so_exit_perror(const char *message, int exit_code);
void	so_print_error(const char *message, int exit_code);
void	so_print_perror(const char *message, int exit_code);

/* ---------------------------- Memory Managing ----------------------------- */

void	so_free_arr(char **arr, size_t arr_size);

#endif

/**
 * @note Error codes:
 * - 100: The program received the wrong number of arguments.
 * - 101: The map file has an incorrect extension (not '.ber').
 * - 102: Failed to open the map file..
 * 
 * - 103: Invalid character detected in the map line.
 * - 104: Incorrect number of columns. Map isn't rectangular.
 * - 105: The map file is empty.
 * - 106: More than one exit or player found in the map.
 * - 107: There's no one collectible found in the map
 * - 108: The map isn't surrounded by walls.
 * - 109: 
 * 
 * - 110: Memory allocation failed.
 * - 111: DFS failed
 */