/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:16:12 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 18:42:49 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static void	make_decision_to_move(t_game *game, int32_t x_px, int32_t y_px);

/* --------------------------- Public Functions ---------------------------- */

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

static void	make_decision_to_move(t_game *game, int32_t x_px, int32_t y_px)
{
	int32_t	y_coor;
	int32_t	x_coor;

	y_coor = y_px / game->player->width;
	x_coor = x_px / game->player->width;
	if (MAP_CODE[1] == game->map->map_arr[y_coor][x_coor])
		return ;
	game->player->instances->y = y_px;
	game->player->instances->x = x_px;
}
