/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_anim_coin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:16:03 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/21 22:32:36 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	t_game		*g;
	uint32_t	x;
	uint32_t	y;

	g = param;
	g->elapsed_time += g->mlx->delta_time;
	if (g->elapsed_time >= g->coin->fps)
	{
		g->elapsed_time -= g->coin->fps;
		g->coin->curr_frame = (g->coin->curr_frame + 1) % g->coin->cnt_frame;
		so_clean_layout(g, FOREGRND);
		y = 0;
		while (y < g->map->row)
		{
			x = 0;
			while ('\0' != g->map->map_arr[y][x])
			{
				if (MAP_CODE[2] == g->map->map_arr[y][x])
					so_draw_anim(g, x, y, FOREGRND);
				x++;
			}
			y++;
		}
	}
}
