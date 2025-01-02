/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_anim_enemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:46:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/02 02:17:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static void		draw_enemy_anim(t_game *g, int i);
static void		set_next_position(t_game *g, int i, const int dir[4][2]);
static t_bool	is_occupied(t_game *g, int i, int x, int y);
static t_bool	is_player_here(t_game *g);

/* --------------------------- Public Functions ---------------------------- */

void	so_set_enemy_hook(void *param)
{
	const int	dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int			i;
	t_game		*g;

	g = param;
	if (PLAY != g->status)
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
			if (is_player_here(g))
				g->status = LOSE;
			i++;
		}
	}
}

/* ------------------- Private Function Implementation --------------------- */

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
		g->enemy.xyd[i][2] = rand() % GO_MAX;
		return ;
	}
	g->enemy.xyd[i][0] += (step * dir[g->enemy.xyd[i][2]][0]);
	g->enemy.xyd[i][1] += (step * dir[g->enemy.xyd[i][2]][1]);
}

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
