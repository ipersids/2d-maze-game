/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:52:27 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/05 18:29:39 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <fcntl.h>			// open
# include <unistd.h>		// close, read, write
# include <stdlib.h>		// malloc, free, exit
# include <stdio.h>			// perror
# include <string.h>		// strerror
// # include <math.h>		// math library

# include "ft_printf.h"		// ft_printf library

# ifndef WIDTH
#  define WIDTH 1366
# endif

# ifndef HEIGHT
#  define HEIGHT 768
# endif

# define NAME "So loooooooooooong game!"
# define MAP_EXTENSION ".ber"
# define MAP_CODE "01CEP"

typedef struct s_map
{
	int		item;
	int		row;
	int		col;
	char	*map_arr;
}			t_map;

void	input_esc_hook(void *param);
void	input_move_hook(mlx_key_data_t keydata, void *param);
int		is_args_valid(int argc, char **argv);
int		is_path_valid(char *path);

#endif