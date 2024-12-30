/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_game_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 22:19:25 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/30 13:38:10 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static void	menu_handler(t_game *g);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets the hook for updating the game screen based on the game state.
 * 
 * This function updates the game screen based on the current game state 
 * (MENU, WIN, LOSE). It handles drawing the appropriate screen images 
 * and disabling the player when necessary.
 * 
 * @param param Pointer to the game structure.
 */
void	so_set_screen_hook(void *param)
{
	t_game		*g;

	g = param;
	if (MENU == g->status)
		menu_handler(g);
	if (WIN == g->status)
	{
		so_clean_layout(g, ENEMYGRND);
		g->pl.player->enabled = false;
		so_draw_screen(g, g->layout[FOREGRND], g->screen.img[SCREEN_WIN]);
	}
	if (LOSE == g->status)
	{
		so_clean_layout(g, ENEMYGRND);
		so_clean_layout(g, FOREGRND);
		g->pl.player->enabled = false;
		so_draw_screen(g, g->layout[FOREGRND], g->screen.img[SCREEN_WIN]);
	}
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Handles the menu screen initialization and drawing.
 * 
 * This function initializes the menu screen if it hasn't been initialized yet.
 * It sets the current frame to the menu screen and draws the background.
 * 
 * @param g Pointer to the game structure.
 */
static void	menu_handler(t_game *g)
{
	static int	menu_is_init = 0;
	int32_t		x;
	int32_t		y;

	if (!menu_is_init)
	{
		g->screen.curr_frame = SCREEN_MENU_RED;
		so_draw_background(g);
		menu_is_init = 1;
	}
	so_clean_layout(g, FOREGRND);
	so_draw_screen(g, g->layout[FOREGRND], g->screen.img[g->screen.curr_frame]);
	if (mlx_is_key_down(g->mlx, MLX_KEY_ENTER))
	{
		so_clean_layout(g, ENEMYGRND);
		x = g->pl.x * g->sprite_size;
		y = g->pl.y * g->sprite_size;
		g->pl.player = g->src_img[g->screen.curr_frame + PL_GREEN];
		mlx_image_to_window(g->mlx, g->pl.player, x, y);
		g->status = PLAY;
	}
}
