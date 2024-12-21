/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:20:07 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/21 17:11:05 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_bg_path(t_background_type type);
static mlx_image_t	**get_bg_images(t_game *g, mlx_image_t *images[BG_MAX]);
static int			get_background_type(t_map *map, size_t x, size_t y);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Draws the map as a background image.
 * 
 * @param game Pointer to the game structure containing the map.
 * @return mlx_image_t* Pointer to the newly created background image, 
 * 						or NULL if creation fails.
 */
mlx_image_t	*so_draw_background(t_game *game)
{
	mlx_image_t	*images[BG_MAX];
	size_t		x;
	size_t		y;
	int32_t		type;

	if (!get_bg_images(game, images))
		return (NULL);
	y = 0;
	while (y < game->map->row)
	{
		x = 0;
		while ('\0' != game->map->map_arr[y][x])
		{
			type = get_background_type(game->map, x, y);
			so_draw_img(game->layout[BACKGRND], images[type], \
						x * game->sprite_size, y * game->sprite_size);
			x++;
		}
		y++;
	}
	so_destroy_images(game->mlx, BG_MAX, images);
	return (game->layout[BACKGRND]);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Gets the file path for a background texture based on its type.
 * 
 * @param type The background type.
 * @return const char* The file path for the background texture.
 */
static const char	*get_bg_path(t_background_type type)
{
	static char	list[BG_MAX][100] = {
		"textures/kenney/background/corner_right_up.png",
		"textures/kenney/background/corner_right_down.png",
		"textures/kenney/background/corner_left_up.png",
		"textures/kenney/background/corner_left_down.png",
		"textures/kenney/background/wall_up.png",
		"textures/kenney/background/wall_down.png",
		"textures/kenney/background/wall_left.png",
		"textures/kenney/background/wall_right.png",
		"textures/kenney/background/floor_wall_tree.png",
		"textures/kenney/background/floor_free_plants.png",
		"textures/kenney/background/exit_stairs_down.png"
	};

	return (list[type]);
}

/**
 * @brief Loads background images for different background types.
 * 
 * @param g Pointer to the game structure.
 * @param images Array of pointers to store the loaded background images.
 * @return mlx_image_t** Array of pointers to the loaded background images, 
 * 						 or NULL if loading fails.
 */
static mlx_image_t	**get_bg_images(t_game *g, mlx_image_t *images[BG_MAX])
{
	int	i;

	i = 0;
	while (i < BG_MAX)
	{
		images[i] = so_load_sprite(get_bg_path(i), g->mlx, g->sprite_size);
		if (!images[i])
		{
			so_destroy_images(g->mlx, i, images);
			return (NULL);
		}
		i++;
	}
	return (images);
}

/**
 * @brief Determines the background type for a given map position.
 * 
 * @param map Pointer to the map structure.
 * @param x The x-coordinate on the map.
 * @param y The y-coordinate on the map.
 * @return int The background type for the given map position.
 */
static int	get_background_type(t_map *map, size_t x, size_t y)
{
	if (map->map_arr[y][x] == MAP_CODE[1])
	{
		if (0 == x && 0 == y)
			return (CORNER_UL);
		if (map->col - 1 == x && 0 == y)
			return (CORNER_UR);
		if (0 == x && map->row - 1 == y)
			return (CORNER_DL);
		if (map->col - 1 == x && map->row - 1 == y)
			return (CORNER_DR);
		if (0 == x)
			return (WALL_L);
		if (map->row - 1 == y)
			return (WALL_D);
		if (0 == y)
			return (WALL_U);
		if (map->col - 1 == x)
			return (WALL_R);
		return (FLOOR_WALL);
	}
	if (map->map_arr[y][x] == MAP_CODE[3])
		return (WAY_OUT);
	return (FLOOR_FREE);
}
