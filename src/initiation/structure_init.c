/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:31 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 00:36:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes the game structure with default values.
 * 
 * @param game Pointer to the game structure.
 * @param map Pointer to the map structure.
 */
void	so_game_init(t_game *game, t_map *map)
{
	game->layout[0] = NULL;
	game->mlx = NULL;
	game->width = WIDTH;
	game->height = HEIGHT;
	game->sprite_size = SPRITE_SIZE_MAX;
	game->elapsed_time = 0;
	game->status = PLAY;
	so_player_init(&game->pl, map);
	so_anim_init(&game->coin, COIN_CNT, COIN_SPEED);
	so_level_init(&game->lvl, map);
}

/**
 * @brief Initializes the map structure with default values.
 * 
 * @param map Pointer to the map structure.
 */
void	so_map_init(t_map *map)
{
	map->col = 0;
	map->row = 0;
	map->exit = 0;
	map->item = 0;
	map->player = 0;
	map->map_arr = NULL;
	map->p_yx[0] = 0;
	map->p_yx[1] = 0;
}

/**
 * @brief Initializes the animation structure with default values.
 * 
 * @param anim Pointer to the animation structure.
 * @param cnt_frame Number of frames in the animation.
 * @param speed Speed of the animation.
 */
void	so_anim_init(t_anim *anim, int32_t cnt_frame, double speed)
{
	anim->img[0] = NULL;
	anim->cnt_frame = cnt_frame;
	anim->curr_frame = 0;
	anim->speed = speed;
	anim->fps = 1.0 / (speed * cnt_frame);
}

/**
 * @brief Initializes the player structure.
 * 
 * @param player Pointer to the player structure.
 * @param map Pointer to the map structure.
 */
void	so_player_init(t_player *player, t_map *map)
{
	player->player = NULL;
	player->move_cnt = 0;
	player->x = map->p_yx[1];
	player->y = map->p_yx[0];
}

/**
 * @brief Initializes the level structure.
 * 
 * @param level Pointer to the level structure.
 * @param map Pointer to the map structure.
 */
void	so_level_init(t_level *level, t_map *map)
{
	level->map = map->map_arr;
	level->col = map->col;
	level->items = map->item;
	level->row = map->row;
}
