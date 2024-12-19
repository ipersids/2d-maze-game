/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:20:07 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/19 20:02:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_bg_path(t_background_type type);
static mlx_image_t	**get_bg_images(t_game *game, mlx_image_t *images[BG_MAX]);
static int			get_background_type(t_map *map, int32_t x, int32_t y);

/* --------------------------- Public Functions ---------------------------- */

mlx_image_t	*so_draw_background(t_game *game)
{
	mlx_image_t	*images[BG_MAX];
	int32_t		x;
	int32_t		y;
	int32_t		type;

	if (!get_bg_img(game, images))
		return (NULL);
	y = 0;
	while (y < game->map->col)
	{
		x = 0;
		while ('\0' != game->map->map_arr[y][x])
		{
			type = get_background_type(game->map, x, y);
			so_draw_img(game->layout[BACKGRND], images[type], \
						x * game->spite_size, y * game->spite_size);
			x++;
		}
		y++;
	}
	so_destroy_images(game->mlx, BG_MAX, images);
	return (game->layout[BACKGRND]);
}

/* ------------------- Private Function Implementation --------------------- */

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

static mlx_image_t	**get_bg_images(t_game *game, mlx_image_t *images[BG_MAX])
{
	int	i;

	i = 0;
	while(i < BG_MAX)
	{
		images[i] = so_load_sprite(get_bg_path(i), game->mlx, game->spite_size);
		if (!images[i])
		{
			so_destroy_images(game->mlx, BG_MAX, images);
			return (NULL);
		}
		i++;
	}
	return (images);
}

static int	get_background_type(t_map *map, int32_t x, int32_t y)
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
	return (FLOOR_FREE);
}
