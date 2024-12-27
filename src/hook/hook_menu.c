/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 22:19:25 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/27 17:35:42 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	so_set_menu_hook(void *param)
{
	static	int	menu_is_init = 0;
	t_game		*g;
	int32_t		x;
	int32_t		y;

	g = param;
	if (MENU != g->status)
		return ;
	if (!menu_is_init)
	{
		g->screen.curr_frame = SCREEN_MENU_RED;
		menu_is_init = 1;
	}
	so_clean_layout(g, FOREGRND);
	so_draw_screen(g, g->layout[FOREGRND], g->screen.img[g->screen.curr_frame]);
	if (mlx_is_key_down(g->mlx, MLX_KEY_ENTER))
	{
		so_clean_layout(g, FOREGRND);
		x = g->pl.x * g->sprite_size;
		y = g->pl.y * g->sprite_size;
		g->pl.player = g->src_img[g->screen.curr_frame + PL_GREEN];
		mlx_image_to_window(g->mlx, g->pl.player, x, y);
		g->status = PLAY;
	}
}
