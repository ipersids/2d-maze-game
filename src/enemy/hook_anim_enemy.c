/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_anim_enemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:46:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/02 17:34:52 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static void		draw_enemy_anim(t_game *g, int i);
static void		set_next_position(t_game *g, int i, const int dir[4][2]);
static t_bool	is_occupied(t_game *g, int i, int x, int y);
static t_bool	is_player_here(t_game *g);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets the hook for updating the enemy animation.
 * 
 * This function updates the enemy animation based on the elapsed time. 
 * It increments the current frame of the enemy animation and redraws 
 * the enemies on the enemy layout.
 * It also handles enemy movement and checks for player collisions.
 * 
 * @param param Pointer to the game structure.
 */
void	so_set_enemy_hook(void *param)
{
	const int	dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int			i;
	t_game		*g;

	g = param;
	if (PLAY != g->status || 0 == g->enemy.cnt)
		return ;
	g->enemy.elapsed_time += g->mlx->delta_time;
	if (g->enemy.elapsed_time >= g->enemy.fps)
	{
		g->enemy.elapsed_time -= g->enemy.fps;
		g->enemy.curr_frame = (g->enemy.curr_frame + 1) % g->enemy.cnt_frame;
		so_clean_layout(g, ENEMYGRND);
		i = 0;
		while (i < g->enemy.cnt)
		{
			if (0 != g->pl.move_cnt)
				set_next_position(g, i, dir);
			draw_enemy_anim(g, i);
			if (is_player_here(g) && 0 != g->pl.move_cnt)
				g->status = LOSE;
			i++;
		}
	}
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Sets the next position for the enemy based on its current direction.
 * 
 * This function calculates the next position for the enemy based on its current
 * direction and updates its coordinates. It also checks for collisions 
 * with walls and other enemies, and changes direction if necessary.
 * 
 * @param g Pointer to the game structure.
 * @param i Index of the enemy in the enemy array.
 * @param dir Array of direction vectors.
 */
static void	set_next_position(t_game *g, int i, const int dir[4][2])
{
	uint32_t	x;
	uint32_t	y;
	int			step;

	step = g->sprite_size / g->enemy.cnt_frame;
	x = g->enemy.xyd[i][0] + (step * dir[g->enemy.xyd[i][2]][0]);
	y = g->enemy.xyd[i][1] + (step * dir[g->enemy.xyd[i][2]][1]);
	if (GO_RIGHT == g->enemy.xyd[i][2])
		x = g->enemy.xyd[i][0] + g->sprite_size;
	if (GO_DOWN == g->enemy.xyd[i][2])
		y = g->enemy.xyd[i][1] + g->sprite_size;
	if (MAP_CODE[1] == g->lvl.map[y / g->sprite_size][x / g->sprite_size] \
		|| is_occupied(g, i, x / g->sprite_size, y / g->sprite_size))
	{
		g->enemy.xyd[i][2] = ft_rand() % GO_MAX;
		return ;
	}
	g->enemy.xyd[i][0] += (step * dir[g->enemy.xyd[i][2]][0]);
	g->enemy.xyd[i][1] += (step * dir[g->enemy.xyd[i][2]][1]);
}

/**
 * @brief Checks if the specified position is occupied by another enemy.
 * 
 * @param g Pointer to the game structure.
 * @param i Index of the current enemy in the enemy array.
 * @param x The x-coordinate of the position to check.
 * @param y The y-coordinate of the position to check.
 * @return t_bool True if the position is occupied, false otherwise.
 */
static t_bool	is_occupied(t_game *g, int i, int x, int y)
{
	int	j;
	int	jx;
	int	jy;

	j = 0;
	while (j < g->enemy.cnt)
	{
		jx = g->enemy.xyd[j][0] / g->sprite_size;
		jy = g->enemy.xyd[j][1] / g->sprite_size;
		if (i != j && x == jx && y == jy)
			return (TRUE);
		j++;
	}
	return (FALSE);
}

/**
 * @brief Draws the enemy animation at the specified position.
 * 
 * @param g Pointer to the game structure.
 * @param i Index of the enemy in the enemy array.
 */
static void	draw_enemy_anim(t_game *g, int i)
{
	mlx_image_t	*dst;
	mlx_image_t	*src;
	int			frame;
	int			px_x;
	int			px_y;

	dst = g->layout[ENEMYGRND];
	frame = g->enemy.curr_frame + g->enemy.xyd[i][2] * g->enemy.cnt_frame;
	src = g->enemy.img[frame];
	px_x = g->enemy.xyd[i][0];
	px_y = g->enemy.xyd[i][1];
	so_draw_img(dst, src, px_x, px_y);
}

/**
 * @brief Checks if the player is at the same position as any enemy.
 * 
 * @param g Pointer to the game structure.
 * @return t_bool True if the player is at the same position as an enemy, 
 * 				  false otherwise.
 */
static t_bool	is_player_here(t_game *g)
{
	int	x;
	int	y;
	int	pl_x;
	int	pl_y;
	int	i;

	i = 0;
	pl_x = g->pl.player->instances[0].x / g->sprite_size;
	pl_y = g->pl.player->instances[0].y / g->sprite_size;
	while (i < g->enemy.cnt)
	{
		x = g->enemy.xyd[i][0] / g->sprite_size;
		y = g->enemy.xyd[i][1] / g->sprite_size;
		if (GO_RIGHT == g->enemy.xyd[i][2])
			x++;
		if (GO_DOWN == g->enemy.xyd[i][2])
			y++;
		if (x == pl_x && y == pl_y)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
