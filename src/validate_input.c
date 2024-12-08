/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:51:32 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/09 00:26:10 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if the program arguments are valid.
 * 
 * The program expects exactly two arguments: <program> <path-to-map>.
 * The map file extension should be '.ber'.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv An array of strings representing the arguments passed
 *             to the program.
 * @return int A file descriptor for the opened map file.
 * 
 * @note If an error occurs, the program exits with one of the codes:
 * 			- 100: The program received the wrong number of arguments.
 * 			- 101: The map file has an incorrect extension (not '.ber').
 * 			- 102: Failed to open the map file.
 */
int	is_args_valid(int argc, char **argv)
{
	size_t	i;
	int		fd;

	if (2 != argc)
		so_exit_error("Usage: ./so_long path/map.ber", 100);
	i = ft_strlen(argv[1]) - ft_strlen(EXTENSION);
	if (0 > i || ft_memcmp(&(argv[1][i]), &EXTENSION, sizeof(EXTENSION)))
		so_exit_error("Wrong map extension.", 101);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd)
		so_exit_perror("Opening file failed", 102);
	return (fd);
}

/**
 * @brief Validates the content of a map line.
 * 
 * This function checks if the line contains only valid characters
 * and if the map rows have the same number of columns 
 * (the map should be rectangular).
 * 
 * @param map A pointer to the map structure.
 * @param y A current y-axis index (rows)
 * 
 * @note If an error occurs, the program exits with one of the codes:
 *			- 103: Invalid character detected in the map line.
 *			- 104: Incorrect number of columns.
 */
void	is_line_valid(t_map *map, size_t y)
{
	size_t	i;

	i = 0;
	while ('\0' != map->map_arr[y][i])
	{
		if (ft_strchr(MAP_CODE, map->map_arr[y][i]) == NULL)
		{
			so_free_arr(map->map_arr, map->row);
			so_exit_error("Invalid map: check forbidden characters.", 103);
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
		so_free_arr(map->map_arr, map->row);
		so_exit_error("Invalid map: check the number of columns.", 104);
	}
}

/**
 * @brief Validates the map contents.
 * 
 * Ensures the map has exactly one player, one exit and at least one item,
 * checks that the map is surrounded by walls. If any validation fails, 
 * the program terminates with an error message.
 * 
 * @param map A pointer to the map structure, which tracks map content.
 * 
 * * @note If an error occurs, the program exits with one of the codes:
 *			- 106: More than one exit or player found in the map.
 *			- 107: There's no one collectible found in the map.
 *			- 108: The map isn't surrounded by walls.
 *
 */
void	is_map_valid(t_map *map)
{
	if (1 != map->exit || 1 != map->player)
	{
		so_free_arr(map->map_arr, map->row);
		so_exit_error("Invalid map: wrong amount of exits/players.", 106);
	}
	if (0 == map->item)
	{
		so_free_arr(map->map_arr, map->row);
		so_exit_error("Invalid map: no one collectible found", 107);
	}
	if (!is_borders_valid(map, MAP_CODE[1]))
	{
		so_free_arr(map->map_arr, map->row);
		so_exit_error("Invalid map: it isn't surrounded by walls", 108);
	}
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
 * @return t_bool Returns `TRUE` (1) if the map's borders are correct, 
 * 				  otherwise returns `FALSE` (0).
 */
t_bool	is_borders_valid(t_map *map, const char ch)
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
					return (FALSE);
				i++;
			}
			y++;
			continue ;
		}
		if (map->map_arr[y][0] != ch)
			return (FALSE);
		if (map->map_arr[y][map->col - 1] != ch)
			return (FALSE);
		y++;
	}
	return (TRUE);
}
