/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:52:27 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/07 12:51:32 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <fcntl.h>			// open
# include <stdio.h>			// perror
# include <string.h>		// strerror
// # include <math.h>		// math library

# include "libft.h"			// libft library

# ifndef WIDTH
#  define WIDTH 1366
# endif

# ifndef HEIGHT
#  define HEIGHT 768
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
# define DEFAULT "\033[0m"

typedef struct s_map
{
	size_t	item;
	size_t	row;
	size_t	col;
	size_t	player;
	size_t	exit;
	char	*map_arr;
}			t_map;

void	input_esc_hook(void *param);
void	input_move_hook(mlx_key_data_t keydata, void *param);
int		is_args_valid(int argc, char **argv);

/* ---------------------------- Error Handling ----------------------------- */

void	so_exit_error(const char *message, int exit_code);
void	so_exit_perror(const char *message, int exit_code);

#endif

/**
 * @note Error codes:
 * - 100: The program received the wrong number of arguments.
 * - 101: The map file has an incorrect extension (not '.ber').
 * - 102: Failed to open the map file (e.g., file not found or permission denied).
 */