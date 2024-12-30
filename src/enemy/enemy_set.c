/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:34:43 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/30 18:24:53 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static int	calculate_enemies(t_game *game, double difficulty);
static int	**allocate_free_spaces_arr(t_game *game);
static void	fill_free_spaces_arr(t_game *game, int **free_spaces);
static int	place_enemy(t_game *game, t_map *map, int **free_spaces);

/* --------------------------- Public Functions ---------------------------- */

void	so_set_enemies(t_game *game, t_map *map)
{
	int	**free_spaces;

	game->lvl.enemy = calculate_enemies(game, DIFFICULTY);
	ft_printf("Possible amount of enemies: %d\n", game->lvl.enemy);
	if (0 == game->lvl.enemy)
		return ;
	free_spaces = allocate_free_spaces_arr(game);
	if (!free_spaces)
	{
		so_destroy_game(game);
		so_exit_error(ERR_SYSTEM);
	}
	game->lvl.enemy = place_enemy(game, map, free_spaces);
	ft_printf("Enemies were placed: %d\n", game->lvl.enemy);
	so_free_arr((void **)free_spaces, game->lvl.free_space);
}

/* ------------------- Private Function Implementation --------------------- */

static int	calculate_enemies(t_game *game, double difficulty)
{
	game->lvl.enemy = (int32_t)(game->lvl.free_space * difficulty);
	return (game->lvl.enemy);
}

static int	**allocate_free_spaces_arr(t_game *game)
{
	int	i;
	int	**free_spaces;

	free_spaces = (int **) malloc(game->lvl.free_space * sizeof(int *));
	if (!free_spaces)
		return (NULL);
	i = 0;
	while (game->lvl.free_space > i)
	{
		free_spaces[i] = (int *) malloc(2 * sizeof(int));
		if (!free_spaces[i])
		{
			so_free_arr((void **)free_spaces, i);
			return (NULL);
		}
		i++;
	}
	fill_free_spaces_arr(game, free_spaces);
	return (free_spaces);
}

static void	fill_free_spaces_arr(t_game *game, int **free_spaces)
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
 * @brief 
 * 
 * 1) Randomly choose a free position on the map by index in free_spaces array
 * 2) Temporary place enemy character on the map
 * 3) Check if map is still playable with this enemy (treated as a wall)
 * 4) If the place works, decrease amount of enemies, otherwise undo step 2.
 * 5) after checking this free place, remove this position and decrease counter
 * 
 * @param game 
 * @param map 
 * @param free_spaces 
 * @return int 
 */
static int	place_enemy(t_game *game, t_map *map, int **free_spaces)
{
	int	e;
	int	i;

	e = 0;
	srand((unsigned long int)free_spaces[0]);
	while (e < game->lvl.enemy && 0 != map->free_space)
	{
		i = rand() % map->free_space;
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
