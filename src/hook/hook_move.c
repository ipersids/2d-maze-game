/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:16:12 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 23:44:56 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static void	make_decision_to_move(t_game *game, int32_t x_px, int32_t y_px);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets the hook for player movement based on key input.
 * 
 * This function handles player movement based on key input. 
 * It calls the function to make a decision to move the player.
 * 
 * @param keydata The key data structure containing info about the key event.
 * @param param Pointer to the game structure.
 */
void	so_set_move_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int32_t	y_pixel;
	int32_t	x_pixel;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		y_pixel = game->player->instances->y;
		x_pixel = game->player->instances->x;
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			y_pixel -= game->player->width;
		if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			x_pixel -= game->player->width;
		if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			y_pixel += game->player->width;
		if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			x_pixel += game->player->width;
		make_decision_to_move(game, x_pixel, y_pixel);
	}
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Makes a decision to move the player based on the new position.
 * 
 * This function checks if the new position is valid and updates the player's 
 * position on the map. It also handles interactions with map elements 
 * such as walls and items.
 * 
 * @param game Pointer to the game structure.
 * @param x_px The new x-coordinate in pixels.
 * @param y_px The new y-coordinate in pixels.
 */
static void	make_decision_to_move(t_game *game, int32_t x_px, int32_t y_px)
{
	int32_t	y_arr;
	int32_t	x_arr;

	y_arr = y_px / game->player->width;
	x_arr = x_px / game->player->width;
	if (MAP_CODE[1] == game->map->map_arr[y_arr][x_arr])
		return ;
	if (MAP_CODE[2] == game->map->map_arr[y_arr][x_arr])
	{
		ft_printf("Wow, coin!\n");
		game->map->map_arr[y_arr][x_arr] = 'c';
		game->map->item--;
	}
	if (MAP_CODE[3] == game->map->map_arr[y_arr][x_arr] && 0 == game->map->item)
		ft_printf("You can go... Later! :)\n");
	game->player->instances->y = y_px;
	game->player->instances->x = x_px;
	game->move_cnt++;
	ft_printf("Number of movements: %s%u%s\n", PURPLE, game->move_cnt, DEFAULT);
}
