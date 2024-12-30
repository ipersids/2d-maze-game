/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:20:07 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/30 13:37:01 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static int	get_background_type(t_level *lvl, int32_t x, int32_t y);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Draws the starting images to the layouts BACKGRND and ENEMYGRND.
 * 
 * This function draws the given map on the background layout (BACKGRND) and 
 * empty tiles on the enemy layout (ENEMYGRND) to temporarily hide the map.
 * 
 * @param g Pointer to the game structure containing the map.
 */
void	so_draw_background(t_game *g)
{
	int32_t		x;
	int32_t		y;
	int32_t		type;

	y = 0;
	while (y <= g->lvl.row)
	{
		x = 0;
		while (g->lvl.col > x)
		{
			type = get_background_type(&g->lvl, x, y);
			so_draw_img(g->layout[BACKGRND], g->src_img[type], \
						x * g->sprite_size, y * g->sprite_size);
			if (WALL_R < type && g->lvl.row != y)
				so_draw_img(g->layout[ENEMYGRND], g->src_img[FLOOR_F_EMPTY], \
							x * g->sprite_size, y * g->sprite_size);
			x++;
		}
		y++;
	}
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Determines the background type for a given map position.
 * 
 * @param map Pointer to the map structure.
 * @param x The x-coordinate on the map.
 * @param y The y-coordinate on the map.
 * @return int The background type for the given map position.
 */
static int	get_background_type(t_level *lvl, int32_t x, int32_t y)
{
	if (lvl->row == y)
		return (FLOOR_F_TILES);
	if (lvl->map[y][x] == MAP_CODE[1])
	{
		if (0 == x && 0 == y)
			return (CORNER_UL);
		if (lvl->col - 1 == x && 0 == y)
			return (CORNER_UR);
		if (0 == x && lvl->row - 1 == y)
			return (CORNER_DL);
		if (lvl->col - 1 == x && lvl->row - 1 == y)
			return (CORNER_DR);
		if (0 == x)
			return (WALL_L);
		if (lvl->row - 1 == y)
			return (WALL_D);
		if (0 == y)
			return (WALL_U);
		if (lvl->col - 1 == x)
			return (WALL_R);
		return (FLOOR_W_TREE);
	}
	if (lvl->map[y][x] == MAP_CODE[3])
		return (WAY_OUT);
	return (FLOOR_F_FLOWER);
}
