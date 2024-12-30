/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:43:51 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/30 16:41:42 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Validates the level by checking the map file and its contents.
 * 
 * @param path The file path to the map.
 * @param map Pointer to the map structure.
 */
void	so_validate_level(char *path, t_map *map)
{
	int	fd;
	int	check;

	check = so_validate_path(path, &fd);
	if (check)
		so_exit_error(check);
	map->map_arr = so_read_map(fd);
	close(fd);
	if (!map->map_arr)
		so_exit_error(ERR_SYSTEM);
	check = so_validate_map(map);
	if (check)
	{
		so_free_arr((void **)map->map_arr, map->row);
		so_exit_error(check);
	}
	ft_printf("%sMap is valid.%s\n", GREEN, DEFAULT);
}
