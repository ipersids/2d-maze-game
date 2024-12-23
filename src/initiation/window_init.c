/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:53:11 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 16:26:13 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static t_bool	is_map_size_valid(t_game *game, int32_t width, int32_t height);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Checks if the map size fits the window size and init Main MLX handle.
 * 
 * Set the window size and limits. Store information about width, height and
 * sprite size into game object.
 * 
 * @param t_game pointer to the game object.
 * @return mlx_t* pointer to the MLX42 main object.
 *
 */
mlx_t	*so_mlx_init(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, NAME, true);
	if (!game->mlx)
	{
		so_free_arr(game->lvl.map, game->lvl.row);
		so_exit_error(ERR_MLX42);
	}
	mlx_get_monitor_size(0, &game->width, &game->height);
	if (!is_map_size_valid(game, game->width, game->height))
	{
		so_free_arr(game->lvl.map, game->lvl.row);
		so_exit_error(ERR_MAP_SIZE);
	}
	mlx_set_window_size(game->mlx, game->width, game->height);
	mlx_set_window_limit(game->mlx,
		game->lvl.col * SPRITE_SIZE_MIN, game->lvl.row * SPRITE_SIZE_MIN,
		game->width, game->height);
	return (game->mlx);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Checks if the map size is valid for the given window dimensions.
 * 
 * This function calculates the sprite size based on the window dimensions 
 * and the map dimensions. It checks if the calculated sprite size is within 
 * the valid range and updates the game object's sprite size, width, 
 * and height accordingly.
 * 
 * @param game Pointer to the game object.
 * @param width The width of the window.
 * @param height The height of the window.
 * @return t_bool True if the map size is valid, false otherwise.
 */
static t_bool	is_map_size_valid(t_game *game, int32_t width, int32_t height)
{
	int32_t		w_sprite;
	int32_t		h_sprite;
	uint32_t	sprite_size;

	w_sprite = width / game->lvl.col;
	h_sprite = height / (game->lvl.row + 1);
	sprite_size = ft_min(w_sprite, h_sprite);
	if (sprite_size < SPRITE_SIZE_MIN)
		return (FALSE);
	if (sprite_size > SPRITE_SIZE_MAX)
		sprite_size = SPRITE_SIZE_MAX;
	game->height = sprite_size * (game->lvl.row + 1);
	game->width = sprite_size * game->lvl.col;
	game->sprite_size = sprite_size;
	return (TRUE);
}
