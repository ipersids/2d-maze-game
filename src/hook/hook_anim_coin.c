/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_anim_coin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:16:03 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 18:39:37 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static void	draw_coin_anim(t_game *game, uint32_t x, uint32_t y, t_layout type);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets the hook for updating the coin animation.
 * 
 * This function updates the coin animation based on the elapsed time. 
 * It increments the current frame of the coin animation and redraws the coins
 * on the foreground layout.
 * 
 * @param param Pointer to the game structure.
 */
void	so_set_coin_hook(void *param)
{
	t_game	*g;
	int32_t	x;
	int32_t	y;

	g = param;
	g->elapsed_time += g->mlx->delta_time;
	if (g->elapsed_time >= g->coin.fps)
	{
		g->elapsed_time -= g->coin.fps;
		g->coin.curr_frame = (g->coin.curr_frame + 1) % g->coin.cnt_frame;
		so_clean_layout(g, FOREGRND);
		y = 0;
		while (y < g->lvl.row)
		{
			x = 0;
			while ('\0' != g->lvl.map[y][x])
			{
				if (MAP_CODE[2] == g->lvl.map[y][x])
					draw_coin_anim(g, x, y, FOREGRND);
				x++;
			}
			y++;
		}
	}
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Draws the current frame of the coin animation at the given position.
 * 
 * @param game Pointer to the game structure.
 * @param x The x-coordinate where the animation frame should be drawn.
 * @param y The y-coordinate where the animation frame should be drawn.
 * @param type The layout type where the animation frame should be drawn.
 */
static void	draw_coin_anim(t_game *game, uint32_t x, uint32_t y, t_layout type)
{
	mlx_image_t	*dst;
	mlx_image_t	*src;

	dst = game->layout[type];
	src = game->coin.img[game->coin.curr_frame];
	so_draw_img(dst, src, x * game->sprite_size, y * game->sprite_size);
}
