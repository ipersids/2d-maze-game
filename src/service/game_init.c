/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:31 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 10:10:41 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes the game structure with default values.
 * 
 * @param game Pointer to the game structure to be initialized.
 * @param map Pointer to the map structure to be associated with the game.
 */
void	so_game_init(t_game *game, t_map *map)
{
	game->elapsed_time = 0.0;
	game->coin = NULL;
	game->layout[0] = NULL;
	game->layout[1] = NULL;
	game->layout[2] = NULL;
	so_map_init(map);
	game->map = map;
	game->mlx = NULL;
	game->sprite_size = SPRITE_SIZE_MAX;
	game->m_width = WIDTH;
	game->m_height = HEIGHT;
}

/**
 * @brief Initializes the map structure with default values.
 * 
 * @param map Pointer to the map structure to be initialized.
 */
void	so_map_init(t_map *map)
{
	map->col = 0;
	map->row = 0;
	map->exit = 0;
	map->item = 0;
	map->player = 0;
	map->map_arr = NULL;
	map->e_xy[X] = 0;
	map->e_xy[Y] = 0;
	map->p_xy[X] = 0;
	map->p_xy[Y] = 0;
}
