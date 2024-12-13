/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:34:03 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/13 23:30:44 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static size_t	dfs(t_map *map, size_t *p_xy, int *vis, const int dir[4][2]);
static void		so_set_start_and_exit(t_map *map);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Checks if the map is playable by performing a depth-first search (DFS).
 * 
 * @param map Pointer to the map structure.
 * @return int 0 if playable, overwise - error code.
 * 
 */
int	is_map_playable(t_map *map)
{
	int			*visited;
	size_t		items;
	const int	direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	so_set_start_and_exit(map);
	visited = (int *) ft_calloc(map->col * map->row, sizeof(int));
	if (!visited)
		return (111);
	items = dfs(map, map->p_xy, visited, direction);
	free(visited);
	if (items == (map->item + map->exit))
		return (0);
	return (112);
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
 * @param p_xy Array containing the player's current x and y coordinates.
 * @param vis Pointer to the array tracking visited nodes.
 * @param dir Array of direction vectors for moving up, down, left, and right.
 * @return size_t The number of reachable items and exits.
 * 
 */
static size_t	dfs(t_map *map, size_t *p_xy, int *vis, const int dir[4][2])
{
	size_t	items;
	int		step;
	size_t	new_xy[2];

	if (p_xy[0] < 0 || p_xy[0] >= map->row || p_xy[1] < 0 || p_xy[1] >= map->col
		|| vis[p_xy[0] * map->col + p_xy[1]]
		|| map->map_arr[p_xy[0]][p_xy[1]] == MAP_CODE[1])
		return (0);
	items = 0;
	vis[p_xy[0] * map->col + p_xy[1]] = 1;
	if (map->map_arr[p_xy[0]][p_xy[1]] == MAP_CODE[2]
		|| map->map_arr[p_xy[0]][p_xy[1]] == MAP_CODE[3])
		items++;
	step = 0;
	while (step < 4)
	{
		new_xy[0] = p_xy[0] + dir[step][0];
		new_xy[1] = p_xy[1] + dir[step][1];
		step++;
		items += dfs(map, new_xy, vis, dir);
	}
	return (items);
}

/**
 * @brief Sets the starting and exit positions on the map.
 * 
 * @param map Pointer to the map structure.
 */
static void	so_set_start_and_exit(t_map *map)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (map->map_arr[row] != NULL)
	{
		col = 0;
		while (map->map_arr[row][col] != '\0')
		{
			if (map->map_arr[row][col] == MAP_CODE[3])
			{
				map->e_xy[0] = row;
				map->e_xy[1] = col;
			}
			if (map->map_arr[row][col] == MAP_CODE[4])
			{
				map->p_xy[0] = row;
				map->p_xy[1] = col;
			}
			col++;
		}
		row++;
	}
}
