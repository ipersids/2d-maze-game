/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:04:08 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/10 01:56:30 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_borders_valid(t_map *map, const char ch);

/**
 * @brief Validates the content of a map line.
 * 
 * This function checks if the line contains only valid characters
 * and if the map rows have the same number of columns 
 * (the map should be rectangular).
 * 
 * @param map A pointer to the map structure.
 * @param y A current y-axis index (rows)
 * @return int 	0 if success. If an error occurs, 
 * 				the program return one of the codes:
 *					- 103: Invalid character detected in the map line.
 *					- 104: Incorrect number of columns.
 */
int	is_line_valid(t_map *map, size_t y)
{
	size_t	i;

	i = 0;
	while ('\0' != map->map_arr[y][i])
	{
		if (ft_strchr(MAP_CODE, map->map_arr[y][i]) == NULL)
		{
			so_print_error("Invalid map: check forbidden characters.", 103);
			return (103);
		}
		if (map->map_arr[y][i] == MAP_CODE[2])
			map->item++;
		if (map->map_arr[y][i] == MAP_CODE[3])
			map->exit++;
		if (map->map_arr[y][i++] == MAP_CODE[4])
			map->player++;
	}
	if (i != map->col || 0 == i)
	{
		so_print_error("Invalid map: check the number of columns.", 104);
		return (104);
	}
	return (0);
}

/**
 * @brief Validates the map contents.
 * 
 * Ensures the map has exactly one player, one exit and at least one item,
 * checks that the map is surrounded by walls. If any validation fails, 
 * the program terminates with an error message.
 * 
 * @param map A pointer to the map structure, which tracks map content.
 * @return int 	0 if success. If an error occurs, 
 * 				the program return one of the codes:
 *					- 106: More than one exit or player found in the map.
 *					- 107: There's no one collectible found in the map.
 *					- 108: The map isn't surrounded by walls.
 *
 */
int	is_map_valid(t_map *map)
{
	if (1 != map->exit || 1 != map->player)
	{
		so_print_error("Invalid map: wrong amount of exits/players.", 106);
		return (106);
	}
	if (0 == map->item)
	{
		so_print_error("Invalid map: no one collectible found", 107);
		return (107);
	}
	if (is_borders_valid(map, MAP_CODE[1]))
	{
		so_print_error("Invalid map: it isn't surrounded by walls", 108);
		return (108);
	}
	if (is_map_playable(map))
	{
		so_print_error("Invalid map: there is no way to win", 112);
		return (112);
	}
	return (0);
}

/**
 * @brief  Checks if the map rows are fully bordered 
 * 		   with the specified character
 * 
 * This function checks that the first and last rows of the map are entirely 
 * composed of the specified border character and that the first and last 
 * characters of each row are the specified border character.
 * 
 * @param map A pointer to the map structure.
 * @param ch The character to check for as the border.
 * @return int Returns 0 if the map's borders are correct, 
 * 				  otherwise returns `108` (error).
 */
static int	is_borders_valid(t_map *map, const char ch)
{
	size_t	y;
	size_t	i;

	y = 0;
	while (y < map->row)
	{
		if (0 == y || y == map->row - 1)
		{
			i = 0;
			while ('\0' != map->map_arr[y][i])
			{
				if (map->map_arr[y][i] != ch)
					return (108);
				i++;
			}
			y++;
			continue ;
		}
		if (map->map_arr[y][0] != ch)
			return (108);
		if (map->map_arr[y][map->col - 1] != ch)
			return (108);
		y++;
	}
	return (0);
}
