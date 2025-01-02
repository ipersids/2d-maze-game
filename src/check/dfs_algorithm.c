/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:34:03 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/30 18:16:37 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static int32_t	dfs(t_map *map, int32_t *p_yx, int *vis, const int dir[4][2]);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Checks if the map is playable by performing a depth-first search (DFS).
 * 
 * @param map Pointer to the map structure.
 * @return int 0 if playable, overwise - error code.
 * 
 */
int	so_validate_map_playable(t_map *map)
{
	int			*visited;
	int32_t		items;
	const int	direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	visited = (int *) ft_calloc(map->col * map->row, sizeof(int));
	if (!visited)
		return (ERR_SYSTEM);
	items = dfs(map, map->p_yx, visited, direction);
	free(visited);
	if (items == (map->item + map->exit))
		return (0);
	return (ERR_DFS);
}
/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Depth-first search (DFS) to count reachable items and exits.
 * 
 * This function recursively explores the map from the player's starting 
 * position, marking visited nodes and counting the number of reachable items 
 * and exit.
 * 
 * @param map Pointer to the map structure.
 * @param p_yx Array containing the player's current x and y coordinates.
 * @param vis Pointer to the array tracking visited nodes.
 * @param dir Array of direction vectors for moving up, down, left, and right.
 * @return int32_t The number of reachable items and exits.
 * 
 */
static int32_t	dfs(t_map *map, int32_t *p_yx, int *vis, const int dir[4][2])
{
	int32_t	items;
	int		step;
	int32_t	new_xy[2];

	if (p_yx[0] < 0 || p_yx[0] >= map->row || p_yx[1] < 0 || p_yx[1] >= map->col
		|| vis[p_yx[0] * map->col + p_yx[1]]
		|| MAP_CODE[1] == map->map_arr[p_yx[0]][p_yx[1]]
		|| ENEMY_CODE == map->map_arr[p_yx[0]][p_yx[1]])
		return (0);
	items = 0;
	vis[p_yx[0] * map->col + p_yx[1]] = 1;
	if (map->map_arr[p_yx[0]][p_yx[1]] == MAP_CODE[2]
		|| map->map_arr[p_yx[0]][p_yx[1]] == MAP_CODE[3])
		items++;
	step = 0;
	while (4 > step)
	{
		new_xy[0] = p_yx[0] + dir[step][0];
		new_xy[1] = p_yx[1] + dir[step][1];
		step++;
		items += dfs(map, new_xy, vis, dir);
	}
	return (items);
}
