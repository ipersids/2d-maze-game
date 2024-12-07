/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:51:32 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/07 21:44:33 by ipersids         ###   ########.fr       */
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
 * @param line The current line of the map to be validated.
 * @param map A pointer to the map structure.
 * @param fd The file descriptor of the map file.
 * 
 * @return size_t The number of valid columns in the map line.
 * 
 * @note If an error occurs, the program exits with one of the codes:
 *			- 103: Invalid character detected in the map line.
 *			- 104: Incorrect number of columns.
 */
size_t	is_line_valid(char *line, t_map *map, int fd)
{
	size_t	i;

	i = 0;
	while ('\0' != line[i] && '\n' != line[i])
	{
		if (ft_strchr(MAP_CODE, line[i]) == NULL)
		{
			so_free_str_close_fd(line, map->map_arr, fd);
			so_exit_error("Invalid map: check forbidden characters.", 103);
		}
		if (line[i] == MAP_CODE[2])
			map->item++;
		if (line[i] == MAP_CODE[3])
			map->exit++;
		if (line[i++] == MAP_CODE[4])
			map->player++;
	}
	if (1 != map->row && (i != map->col || 0 == i))
	{
		so_free_str_close_fd(line, map->map_arr, fd);
		so_exit_error("Invalid map: check the number of columns.", 104);
	}
	return (i);
}

/**
 * @brief Validates the map contents.
 * 
 * Ensures the map has exactly one player, one exit and at least one item,
 * checks that the map is surrounded by walls. If any validation fails, 
 * the program terminates with an error message.
 * 
 * @param line The current map line being validated.
 * @param map A pointer to the map structure, which tracks map content.
 * @param fd The file descriptor of the map file.
 * @param last Indicator if the line is the last row of the map.
 * 
 * * @note If an error occurs, the program exits with one of the codes:
 *			- 106: More than one exit or player found in the map.
 *			- 107: More than one player found in the map.
 *			- 108: The map isn't surrounded by walls.
 *			- 109: The final map statement is invalid.
 */
void	is_map_valid(char *line, t_map *map, int fd, t_bool last)
{
	if (1 < map->exit || 1 < map->player)
	{
		so_free_str_close_fd(line, map->map_arr, fd);
		so_exit_error("Invalid map: more than one exit/player.", 106);
	}
	if (1 < map->player)
	{
		so_free_str_close_fd(line, map->map_arr, fd);
		so_exit_error("Invalid map: more than one player.", 107);
	}
	if (((1 == map->row || TRUE == last) && !is_brow_valid(line, MAP_CODE[1]))
		|| !(MAP_CODE[1] == line[0] && MAP_CODE[1] == line[map->col - 1]))
	{
		so_free_str_close_fd(line, map->map_arr, fd);
		so_exit_error("Invalid map: check if it's surrounded by walls.", 108);
	}
	if (TRUE == last && (1 != map->exit || 1 != map->player || 0 == map->item))
	{
		so_free_str_close_fd(line, map->map_arr, fd);
		so_exit_error("Invalid map: check how many players/exits/items.", 109);
	}
}

/**
 * @brief Checks if a row is fully bordered with the specified character.
 * 
 * @param line The map row to check.
 * @param ch The border character (`1`)
 * @return t_bool Returns `TRUE` (1) if the row is fully bordered, 
 * 				  `FALSE` (0) otherwise.
 */
t_bool	is_brow_valid(const char *line, const char ch)
{
	while ('\0' != *line && '\n' != *line)
	{
		if (ch != *line)
			return (FALSE);
		line++;
	}
	return (TRUE);
}
