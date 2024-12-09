/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:34:03 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/09 18:29:34 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void so_set_start_and_exit(t_map *map);


int	is_map_playable(t_map *map)
{
	so_set_start_and_exit(map);
	// continue
}

static void so_set_start_and_exit(t_map *map)
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
