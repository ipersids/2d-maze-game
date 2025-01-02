/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:04:08 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/30 13:59:51 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static int	is_borders_valid(t_map *map, const char ch);
static int	is_line_valid(t_map *map, int32_t y);
static int	is_map_valid(t_map *map);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Validates the map structure.
 * 
 * This function performs various checks to validate the map structure,
 * ensuring it meets the required criteria for the game.
 * 
 * @param map Pointer to the map structure.
 * @return int 0 if the map is valid, otherwise an error code.
 */
int	so_validate_map(t_map *map)
{
	int		check;
	int32_t	i;

	i = 0;
	map->col = ft_strlen(map->map_arr[0]);
	while (map->map_arr[map->row] != NULL)
		map->row++;
	if (0 == map->col)
		return (ERR_EMPTY_MAP);
	i = 0;
	while (map->map_arr[i] != NULL)
	{
		check = is_line_valid(map, i);
		if (check)
			return (check);
		i++;
	}
	check = is_map_valid(map);
	if (check)
		return (check);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Validates the content of a map line.
 * 
 * This function checks if the line contains only valid characters
 * and if the map rows have the same number of columns 
 * (the map should be rectangular).
 * 
 * @param map A pointer to the map structure.
 * @param y A current y-axis index (rows)
 * @return int 	0 if success. If an error occurs, returns error code.
 */
static int	is_line_valid(t_map *map, int32_t y)
{
	int32_t	i;

	i = 0;
	while ('\0' != map->map_arr[y][i])
	{
		if (ft_strchr(MAP_CODE, map->map_arr[y][i]) == NULL)
			return (ERR_INVALID_CH);
		if (MAP_CODE[0] == map->map_arr[y][i])
			map->free_space++;
		else if (MAP_CODE[2] == map->map_arr[y][i])
			map->item++;
		else if (MAP_CODE[3] == map->map_arr[y][i])
			map->exit++;
		else if (MAP_CODE[4] == map->map_arr[y][i])
		{
			map->p_yx[0] = y;
			map->p_yx[1] = i;
			map->player++;
		}
		i++;
	}
	if (0 == i || i != map->col)
		return (ERR_RECTANGULAR);
	return (0);
}

/**
 * @brief Validates the map contents.
 * 
 * Ensures the map has exactly one player, one exit and at least one item,
 * checks that the map is surrounded by walls and playable. Ensure that
 * the map fits the maximum monitor resolution.
 * 
 * @param map A pointer to the map structure, which tracks map content.
 * @return int 0 if success. If an error occurs, returns error code.
 *
 */
static int	is_map_valid(t_map *map)
{
	if (SPRITE_SIZE_MIN > ft_min(WIDTH / map->col, HEIGHT / (map->row + 1)))
		return (ERR_MAP_SIZE);
	if (1 != map->player)
		return (ERR_PLAYER_CNT);
	if (1 != map->exit)
		return (ERR_EXIT_CNT);
	if (0 == map->item)
		return (ERR_ITEM_CNT);
	if (is_borders_valid(map, MAP_CODE[1]))
		return (ERR_BORDERS);
	if (so_validate_map_playable(map))
		return (ERR_DFS);
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
 * 			   otherwise returns error code.
 */
static int	is_borders_valid(t_map *map, const char ch)
{
	int32_t	y;
	int32_t	i;

	y = 0;
	while (y < map->row)
	{
		if (0 == y || y == map->row - 1)
		{
			i = 0;
			while ('\0' != map->map_arr[y][i])
			{
				if (map->map_arr[y][i] != ch)
					return (ERR_BORDERS);
				i++;
			}
			y++;
			continue ;
		}
		if (map->map_arr[y][0] != ch)
			return (ERR_BORDERS);
		if (map->map_arr[y][map->col - 1] != ch)
			return (ERR_BORDERS);
		y++;
	}
	return (0);
}
