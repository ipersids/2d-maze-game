/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:53:11 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/18 19:02:12 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_bool	is_map_size_valid(t_game *game);

mlx_t	*so_mlx_init(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, NAME, true);
	if (!game->mlx)
	{
		so_free_arr(game->map->map_arr, game->map->row);
		so_exit_error(mlx_strerror(mlx_errno), mlx_errno);
	}
	mlx_get_monitor_size(0, &game->m_width, &game->m_height);
	ft_printf("Monitor: ");
	ft_printf("\twidth = %d,\n\theight = %d\n", game->m_width, game->m_height);
	if (!is_map_size_valid(game))
	{
		so_free_arr(game->map->map_arr, game->map->row);
		mlx_terminate(game->mlx);
		so_exit_error("The map doesn't fit the maximum monitor size", 109);
	}
	return (game->mlx);
}

static t_bool	is_map_size_valid(t_game *game)
{
	int32_t		w_sprite;
	int32_t		h_sprite;
	uint32_t	sprite_size;

	w_sprite = game->m_width / game->map->col;
	h_sprite = game->m_height / game->map->row;
	sprite_size = ft_min(w_sprite, h_sprite);
	if (sprite_size < SPRITE_SIZE_MIN)
	{
		mlx_close_window(game->mlx);
		return (FALSE);
	}
	if (sprite_size > SPRITE_SIZE_MAX)
		sprite_size = SPRITE_SIZE_MAX;
	game->m_height = sprite_size * game->map->row;
	game->m_width = sprite_size * game->map->col;
	game->spite_size = sprite_size;
	mlx_set_window_size(game->mlx, game->m_width, game->m_height);
	mlx_set_window_limit(game->mlx,
		game->map->col * SPRITE_SIZE_MIN, game->map->row * SPRITE_SIZE_MIN,
		game->m_width, game->m_height);
	return (TRUE);
}
