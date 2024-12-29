/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_anim_coin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:16:03 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/25 22:16:37 by ipersids         ###   ########.fr       */
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
	t_game			*g;
	static double	elapsed_time = 0;
	int32_t			xy[2];

	g = param;
	if (PLAY != g->status)
		return ;
	elapsed_time += g->mlx->delta_time;
	if (PLAY == g->status && elapsed_time >= g->coin.fps)
	{
		elapsed_time -= g->coin.fps;
		g->coin.curr_frame = (g->coin.curr_frame + 1) % g->coin.cnt_frame;
		so_clean_layout(g, FOREGRND);
		xy[1] = 0;
		while (xy[1] < g->lvl.row)
		{
			xy[0] = 0;
			while ('\0' != g->lvl.map[xy[1]][xy[0]])
			{
				if (MAP_CODE[2] == g->lvl.map[xy[1]][xy[0]])
					draw_coin_anim(g, xy[0], xy[1], FOREGRND);
				xy[0]++;
			}
			xy[1]++;
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
