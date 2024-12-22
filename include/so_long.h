/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:52:27 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 00:53:24 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** 
 * 	@todo small things:
 *  1) 	dfs_algorithm.c -> dfs()
 * 		Add termination when all items are visited. 
 * 		Check "is_move_safe" separately.
 * 	2)	the image loading for bg and anim could be implemented on more abstract 
 * 		level.
 * 	3)	It might be a good idea to re-add a check for the actual monitor size.
 */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <fcntl.h>			// open
# include <stdio.h>			// perror
# include <string.h>		// strerror
# include <errno.h>			// strerror dependency
// # include <math.h>			// math library

# include "libft.h"			// libft library

// 3840
# ifndef WIDTH
#  define WIDTH 1600
# endif

// 2160
# ifndef HEIGHT
#  define HEIGHT 900
# endif

# define NAME "So loooooooooooong game!"
# define EXTENSION ".ber"

# define SPRITE_SIZE_MIN 32
# define SPRITE_SIZE_MAX 108
# define RGBA 4					// Bytes Per Pixel equal sizeof(int32_t)

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
# define PURPLE "\033[0;35m"
# define DEFAULT "\033[0m"

# define COIN_SPEED 1.0 	// 1 loop per second
# define COIN_CNT 10		// 10 frames in the animation

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
	size_t	p_yx[2];
	size_t	exit;
	char	**map_arr;
}			t_map;

typedef struct s_player
{
	mlx_image_t	*player;
	uint32_t	move_cnt;
	int32_t		x;
	int32_t		y;
}				t_player;

typedef struct s_anim
{
	mlx_image_t	*img[10];
	int			curr_frame;
	int			cnt_frame;
	double		speed;
	double		fps;
}				t_anim;

typedef struct s_level
{
	char	**map;
	int32_t	row;
	int32_t	col;
	int32_t	items;
}			t_level;

typedef struct s_game
{
	mlx_image_t	*layout[3];
	mlx_t		*mlx;
	int32_t		width;
	int32_t		height;
	uint32_t	sprite_size;
	double		elapsed_time;
	int32_t		status;
	t_player	pl;
	t_anim		coin;
	t_level		lvl;
}			t_game;

typedef enum e_status
{
	PLAY,
	WIN,
	LOSE
}	t_status;

typedef enum e_layout
{
	FOREGRND,
	BACKGRND,
	WHITEGRND,
	LAY_MAX
}	t_layout;

typedef enum e_anim_type
{
	ANIM_COIN,
	ANIM_EXIT,
	ANIM_ENEMY,
	ANIM_MAX
}	t_anim_type;

typedef enum e_background_type
{
	CORNER_UR,
	CORNER_DR,
	CORNER_UL,
	CORNER_DL,
	WALL_U,
	WALL_D,
	WALL_L,
	WALL_R,
	FLOOR_WALL,
	FLOOR_FREE,
	WAY_OUT,
	BG_MAX
}	t_background_type;

/* ---------------------------- Initialisation ----------------------------- */

void		so_map_init(t_map *map);
void		so_game_init(t_game *game, t_map *map);
void		so_anim_init(t_anim *anim, int32_t cnt_frame, double speed);
void		so_player_init(t_player *player, t_map *map);
void		so_level_init(t_level *level, t_map *map);
mlx_t		*so_mlx_init(t_game *game);

mlx_image_t	**so_set_layout(t_game *g);
mlx_image_t	**so_set_coin_animation(t_game *game);
void		so_clean_layout(t_game *game, t_layout type);
void 		so_draw_anim(t_game *game, uint32_t x, uint32_t y, t_layout type);

/* --------------------------------- Hooks --------------------------------- */

void		so_set_esc_hook(void *param);
void		so_set_close_hook(void *param);
void		so_set_move_hook(mlx_key_data_t keydata, void *param);
void		so_set_coin_hook(void *param);

/* ---------------------------- Validate Input ----------------------------- */

int			so_validate_level(char *path, t_map *map);
int			so_validate_path(char *path, int *fd);
int			so_validate_map(t_map *map);
int			so_validate_map_playable(t_map *map);

char		**so_read_map(int fd);

/* ---------------------------- Error Handling ----------------------------- */

void		so_exit_error(int exit_code);
void		so_print_error(int exit_code);

/* ----------------------- Memory and MLX42 Managing ------------------------ */

void		so_free_arr(char **arr, size_t arr_size);
void		*so_destroy_images(mlx_t *mlx, int32_t i, mlx_image_t **images);
void		so_destroy_game(t_game *game);

/* -------------------------- Working with Images --------------------------- */

mlx_image_t	*so_load_sprite(const char *path, mlx_t *mlx, uint32_t sprite_size);
uint32_t	so_get_pixel(mlx_image_t *img, uint32_t px_x, uint32_t px_y);
void		so_draw_img(mlx_image_t *dest, mlx_image_t *s, \
						uint32_t x, uint32_t y);
mlx_image_t	*so_draw_background(t_game *game);
mlx_image_t	*so_new_image(mlx_t *mlx, uint32_t w, uint32_t h, int channel);

/* ------------------ TESTING ----- START ----- TESTING --------------------- */
/* ------------------ TESTING ----- START ----- TESTING --------------------- */
/* ------------------ TESTING ----- START ----- TESTING --------------------- */

# define DEFAULT_COLOR 0xFFFFFFFF	// RGBA {255, 255, 255, 255}

/**
 * @note Error codes:
 * 
 * - 98:  System error
 * - 99:  MLX error
 * - 100: The program received the wrong number of arguments.
 * - 101: The map file has an incorrect extension (not '.ber').
 * - 98: Failed to open the map file..
 * 
 * - 103: Invalid character detected in the map line.
 * - 104: Incorrect number of columns. Map isn't rectangular.
 * - 105: The map file is empty.
 * - 106: More than one exit or player found in the map.
 * - 107: There's no one collectible found in the map
 * - 108: The map isn't surrounded by walls.
 * - 109: The map doesn't fit the maximum monitor size.
 * 
 * - 110: Memory allocation failed.
 * - 111: DFS failed
 */

/**
 * @brief 
 * 
 * - ERR_SYSTEM: callback strerror(errno);
 * - ERR_MLX42: callback mlx_strerror(mlx_errno);
 * 
 * 1. ERR_AGRC: The program received the wrong number of arguments.
 * 2. ERR_EXTENSION: The map file has an incorrect extension (not '.ber').
 * 3. ERR_INVALID_CH: Invalid character detected in the map line.
 * 4. ERR_RECTANGULAR: Incorrect number of columns. Map isn't rectangular.
 * 5. ERR_EMPTY_MAP: The map file is empty.
 * 6. ERR_PLAYER_CNT: Incorrect number of players. Should be only one.
 * 7. ERR_EXIT_CNT: Incorrect number of exits. Should be only one.
 * 8. ERR_ITEM_CNT: Incorrect number of collectibles.
 * 9. ERR_BORDERS: The map isn't surrounded by walls.
 * 10. ERR_MAP_SIZE: The map doesn't fit the maximum monitor size.
 * 11. ERR_DFS: Invalid map: there is no way to win.
 * 
 * ERR_MAX - limiter for array of error messages.
 */
typedef enum s_error
{
	ERR_SYSTEM = 98,
	ERR_MLX42,
	ERR_AGRC,
	ERR_EXTENSION,
	ERR_INVALID_CH,
	ERR_RECTANGULAR,
	ERR_EMPTY_MAP,
	ERR_PLAYER_CNT,
	ERR_EXIT_CNT,
	ERR_ITEM_CNT,
	ERR_BORDERS,
	ERR_MAP_SIZE,
	ERR_DFS,
	ERR_MAX
}	t_error;

/* ------------------ TESTING ------ END ------ TESTING --------------------- */
/* ------------------ TESTING ------ END ------ TESTING --------------------- */
/* ------------------ TESTING ------ END ------ TESTING --------------------- */

#endif