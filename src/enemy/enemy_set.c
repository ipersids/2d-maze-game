/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:34:43 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/04 13:09:51 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static void	fill_free_spaces_arr(t_game *game, uint32_t **free_spaces);
static void	fill_enemy_pos_arr(t_game *game, uint32_t **enemy_pos);
static int	put_enemies(t_game *game, t_map *map, uint32_t **free_spaces);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Places enemies on the map.
 * 
 * @param game Pointer to the game structure.
 * @param map Pointer to the map structure.
 * @return uint32_t** Array of enemy positions, or NULL if placement fails.
 */
uint32_t	**so_place_enemies(t_game *game, t_map *map)
{
	uint32_t	**free_spaces;
	uint32_t	**enemy_pos;

	game->enemy.cnt = (int32_t)(game->lvl.free_space * DIFFICULTY);
	ft_printf("Possible amount of enemies: %d\n", game->enemy.cnt);
	if (0 == game->enemy.cnt)
		return (NULL);
	free_spaces = so_allocate_arr(game->lvl.free_space, 2);
	if (!free_spaces)
		return (NULL);
	fill_free_spaces_arr(game, free_spaces);
	game->enemy.cnt = put_enemies(game, map, free_spaces);
	enemy_pos = so_allocate_arr(game->enemy.cnt, 3);
	if (!enemy_pos)
	{
		so_free_arr((void **)free_spaces, game->lvl.free_space);
		return (NULL);
	}
	fill_enemy_pos_arr(game, enemy_pos);
	so_free_arr((void **)free_spaces, game->lvl.free_space);
	return (enemy_pos);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Fills the array with the coordinates of free spaces on the map.
 * 
 * @param game Pointer to the game structure.
 * @param free_spaces Array to store the coordinates of free spaces.
 */
static void	fill_free_spaces_arr(t_game *game, uint32_t **free_spaces)
{
	int	cnt;
	int	row;
	int	col;

	cnt = 0;
	row = 0;
	while (row < game->lvl.row && cnt < game->lvl.free_space)
	{
		col = 0;
		while (col < game->lvl.col && cnt < game->lvl.free_space)
		{
			if (game->lvl.map[row][col] == MAP_CODE[0])
			{
				free_spaces[cnt][0] = col;
				free_spaces[cnt][1] = row;
				cnt++;
			}
			col++;
		}
		row++;
	}
}

/**
 * @brief Places enemy on the map at random free spaces.
 * 
 * 1) Randomly choose a free position on the map by index in free_spaces array
 * 2) Temporary place enemy character on the map
 * 3) Check if map is still playable with this enemy (treated as a wall)
 * 4) If the place works, decrease amount of enemies, otherwise undo step 2.
 * 5) after checking this free place, remove this position and decrease counter
 * 
 * @param game Pointer to the game structure.
 * @param map Pointer to the map structure.
 * @param free_spaces Array of free spaces on the map.
 * @return int The number of enemies successfully placed.
 */
static int	put_enemies(t_game *game, t_map *map, uint32_t **free_spaces)
{
	int	e;
	int	i;

	e = 0;
	while (e < game->enemy.cnt && 0 != map->free_space)
	{
		i = ft_rand() % map->free_space;
		game->lvl.map[free_spaces[i][1]][free_spaces[i][0]] = ENEMY_CODE;
		if (so_validate_map_playable(map))
			game->lvl.map[free_spaces[i][1]][free_spaces[i][0]] = MAP_CODE[0];
		else
			e++;
		map->free_space--;
		free_spaces[i][0] = free_spaces[map->free_space][0];
		free_spaces[i][1] = free_spaces[map->free_space][1];
	}
	return (e);
}

/**
 * @brief Fills the enemy position array with the coordinates of the enemies.
 * 
 * @param game Pointer to the game structure.
 * @param enemy_pos Array to store the enemy positions.
 */
static void	fill_enemy_pos_arr(t_game *game, uint32_t **enemy_pos)
{
	int	i;
	int	row;
	int	col;

	i = 0;
	row = 0;
	while (row < game->lvl.row && i < game->enemy.cnt)
	{
		col = 0;
		while (col < game->lvl.col && i < game->enemy.cnt)
		{
			if (ENEMY_CODE == game->lvl.map[row][col])
			{
				enemy_pos[i][0] = col * game->sprite_size;
				enemy_pos[i][1] = row * game->sprite_size;
				enemy_pos[i][2] = ft_rand() % GO_MAX;
				i++;
			}
			col++;
		}
		row++;
	}
	game->enemy.xyd = enemy_pos;
}
