/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:52:27 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/27 16:53:26 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** 
 * 	@todo small things:
 * 	1) It might be a good idea to re-add a check for the actual monitor size.
 * 	2) Move elapsed time to the animation structure.
 */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <fcntl.h>				// open
# include <stdio.h>				// perror
# include <string.h>			// strerror
# include <errno.h>				// strerror dependency
# include <math.h>				// math library

# include "libft.h"				// libft library

# define WIDTH 3840
# define HEIGHT 2160
# define NAME "So long game!"

# define SPRITE_SIZE_MIN 32		// Minimum size for one sprite in pixels
# define SPRITE_SIZE_MAX 108	// Maximum size for one sprite in pixels
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
# define EXTENSION ".ber" 		// Map file extension 

/**
 * @brief Color palette for ft_printf
 */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define DEFAULT "\033[0m"

/**
 * @brief Constants for animations
 */
# define ANIM_MAX_FRAMES 10	// Maximum size of img array in anim struct
# define COIN_SPEED 1.0 	// 1 loop per second
# define COIN_CNT 10		// 10 frames in the animation
# define NUM_CNT 10			// 10 frames in the animation
# define NUM_ARR_SIZE 6		// 6 digits maximum in the counter

/**
 * @brief Enum representing the game status.
 */
typedef enum e_status
{
	MENU,
	PLAY,
	WIN,
	LOSE
}	t_status;

/**
 * @brief Enum representing the game screens (depend on status).
 */
typedef enum e_screen
{
	SCREEN_MENU_GREEN,
	SCREEN_MENU_RED,
	SCREEN_MENU_YELLOW,
	SCREEN_WIN,
	SCREEN_LOSE,
	SCREEN_MAX
}	t_screen;

/**
 * @brief Enum representing the layout types.
 */
typedef enum e_layout
{
	FOREGRND,
	ENEMYGRND,
	BACKGRND,
	WHITEGRND,
	LAY_MAX
}	t_layout;

/**
 * @brief Enum representing the background types.
 */
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
	FLOOR_TILE,
	FLOOR_FREE,
	WAY_OUT,
	PL_GREEN,
	PL_RED,
	PL_YELLOW,
	BG_MAX
}	t_background_type;

/**
 * @brief Structure representing the map.
 */
typedef struct s_map
{
	char		**map_arr;	/**< Pointer to the map array. */
	int32_t		col;		/**< Number of columns in the map. */
	int32_t		row;		/**< Number of rows in the map. */
	int32_t		exit;		/**< Number of exits in the map. */
	int32_t		item;		/**< Number of items in the map. */
	int32_t		player;		/**< Number of players in the map. */
	int32_t		p_yx[2];	/**< Player's position (y, x). */
	int32_t		e_yx[2];	/**< Exit's position (y, x). */
}				t_map;

/**
 * @brief Structure representing the player.
 */
typedef struct s_player
{
	mlx_image_t	*player;	/**< Pointer to the player's image. */
	uint32_t	move_cnt;	/**< Count of the player's moves. */
	int32_t		x;			/**< X-coordinate of the player's position. */
	int32_t		y;			/**< Y-coordinate of the player's position. */
}				t_player;

/**
 * @brief Structure representing an animation.
 */
typedef struct s_anim
{
	mlx_image_t	*img[ANIM_MAX_FRAMES];		/**< Array of pointers to the anim frames. */
	int32_t		curr_frame;		/**< Current frame of the animation. */
	int32_t		cnt_frame;		/**< Total number of frames in the anim. */
	double		speed;			/**< Speed of the animation. */
	double		fps;			/**< Frames per second of the anim. */
}				t_anim;

/**
 * @brief Structure representing a game level.
 */
typedef struct s_level
{
	char		**map;	/**< Pointer to the map array. */
	int32_t		col;	/**< Number of columns in the map. */
	int32_t		row;	/**< Number of rows in the map. */
	int32_t		items;	/**< Number of items in the level. */
}				t_level;

/**
 * @brief Structure representing the game.
 */
typedef struct s_game
{
	mlx_image_t	*layout[LAY_MAX];	/**< Array of ptrs to the layout images. */
	mlx_t		*mlx;				/**< Pointer to the MLX instance. */
	int32_t		width;				/**< Width of the game window. */
	int32_t		height;				/**< Height of the game window. */
	uint32_t	sprite_size;		/**< Size of the sprites. */
	double		elapsed_time;		/**< Elapsed time since the game started. */
	int32_t		status;				/**< Current status of the game. */
	t_player	pl;					/**< Player information. */
	t_anim		coin;				/**< Coin animation information. */
	t_anim		counter;			/**< Counter animation information. */
	t_anim		screen;	/**< Resources for menu, win and lose screens. */
	t_level		lvl;				/**< Level information. */
	mlx_image_t	*src_img[BG_MAX];	/**< Recourses for drawing game word */
}				t_game;

/* ------------------------ Struct initialisation -------------------------- */

void		so_game_init(t_game *game, t_map *map);
void		so_map_init(t_map *map);
void		so_anim_init(t_anim *anim, int32_t cnt_frame, double speed);
void		so_player_init(t_player *player, t_map *map);
void		so_level_init(t_level *level, t_map *map);

mlx_t		*so_mlx_init(t_game *game);

/* --------------------- Map and arguments validation  --------------------- */

int			so_validate_map_playable(t_map *map);
int			so_validate_level(char *path, t_map *map);
int			so_validate_path(char *path, int *fd);
int			so_validate_map(t_map *map);

char		**so_read_map(int fd);

/* ---------------------- Graphics content management ---------------------- */

mlx_image_t	**so_set_coin_animation(t_game *game);
mlx_image_t	**so_set_num_animation(t_game *game);
mlx_image_t	*so_draw_background(t_game *game);
mlx_image_t	**so_get_imgarray(t_game *g, mlx_image_t **images, int cnt, \
								const char *(*get_path)(int));
void		so_draw_img(mlx_image_t *dest, mlx_image_t *s, \
						uint32_t x, uint32_t y);
uint32_t	so_get_pixel(mlx_image_t *img, uint32_t px_x, uint32_t px_y);
mlx_image_t	*so_new_image(mlx_t *mlx, uint32_t w, uint32_t h, int channel);
mlx_image_t	**so_set_layout(t_game *g);
void		so_clean_layout(t_game *game, t_layout type);
mlx_image_t	*so_load_sprite(const char *path, mlx_t *mlx, uint32_t sprite_size);
mlx_image_t	**so_get_screen_imgs(t_game *game);
void		so_draw_screen(t_game *game, mlx_image_t *dest, mlx_image_t *src);

/* --------------------------------- Hooks --------------------------------- */

void		so_set_esc_hook(void *param);
void		so_set_close_hook(void *param);
void		so_set_move_hook(mlx_key_data_t keydata, void *param);
void		so_set_coin_hook(void *param);
void		so_set_counter_hook(void *param);
void		so_set_menu_hook(void *param);

/* ---------------------- Error and memory management ---------------------- */

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

void		so_exit_error(int exit_code);
void		so_print_error(int exit_code);

void		so_free_arr(char **arr, size_t arr_size);
void		*so_destroy_images(mlx_t *mlx, int32_t i, mlx_image_t **images);
void		so_destroy_game(t_game *game);

#endif