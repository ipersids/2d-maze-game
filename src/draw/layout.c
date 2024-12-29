/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:16:43 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/29 17:34:35 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_background_path(int index);
static mlx_image_t	**get_background_images(t_game *g, mlx_image_t **images);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes the layout images for the game.
 * 
 * This function creates new images for each layout type (foreground, 
 * background, white background). It sets the pixel values for the white 
 * background to 255 (fully opaque) and for other backgrounds to 0 
 * (fully transparent). It then adds these images to the game window and 
 * calls `get_background_images` to load resources for drawing map.
 * 
 * @param g Pointer to the game structure.
 * @return mlx_image_t** Array of pointers to the set layout images, 
 *                      or NULL if creation fails.
 */
mlx_image_t	**so_set_layout(t_game *g)
{
	int	i;
	int	_height;

	i = 0;
	_height = g->height + g->sprite_size;
	while (i < LAY_MAX)
	{
		if (WHITEGRND == i)
			g->layout[i] = so_new_image(g->mlx, g->width, _height, 255);
		else
			g->layout[i] = so_new_image(g->mlx, g->width, _height, 0);
		if (!g->layout[i])
		{
			so_destroy_images(g->mlx, i, g->layout);
			return (NULL);
		}
		i++;
	}
	mlx_image_to_window(g->mlx, g->layout[WHITEGRND], 0, 0);
	mlx_image_to_window(g->mlx, g->layout[BACKGRND], 0, 0);
	mlx_image_to_window(g->mlx, g->layout[ENEMYGRND], 0, 0);
	mlx_image_to_window(g->mlx, g->layout[FOREGRND], 0, 0);
	if (!get_background_images(g, g->src_img))
		return (NULL);
	return (g->layout);
}

/**
 * @brief Cleans the specified layout by setting all its pixels to 0.
 * 
 * @param game Pointer to the game structure.
 * @param type The layout type to be cleaned.
 */
void	so_clean_layout(t_game *game, t_layout type)
{
	mlx_image_t	*layout;

	layout = game->layout[type];
	ft_memset(layout->pixels, 0, layout->width * layout->height * RGBA);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Gets the file path for a background texture based on its type.
 * 
 * @param type The background type.
 * @return const char* The file path for the background texture.
 */
static const char	*get_background_path(int index)
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
		"textures/kenney/background/floor_wall_barrels.png",
		"textures/kenney/background/floor_wall_campfire.png",
		"textures/kenney/background/floor_wall_dragon.png",
		"textures/kenney/background/floor_free_tiles.png",
		"textures/kenney/background/floor_free_plants.png",
		"textures/kenney/background/floor_free_empty_tile.png",
		"textures/kenney/background/floor_free_grass.png",
		"textures/kenney/background/exit_stairs_down.png",
		"textures/kenney/characters/green_character.png",
		"textures/kenney/characters/red_character.png",
		"textures/kenney/characters/yellow_character.png"
	};

	return (list[index]);
}

/**
 * @brief Loads background images for different background types.
 * 
 * @param g Pointer to the game structure.
 * @param images Array of pointers to store the loaded background images.
 * @return mlx_image_t** Array of pointers to the loaded background images, 
 * 						 or NULL if loading fails.
 */
static mlx_image_t	**get_background_images(t_game *g, mlx_image_t **images)
{
	mlx_image_t	**ptr;

	ptr = so_get_imgarray(g, images, BG_MAX, get_background_path);
	return (ptr);
}
