/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:51:32 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/07 12:52:00 by ipersids         ###   ########.fr       */
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
	if (0 >= i || ft_memcmp(&(argv[1][i]), &EXTENSION, sizeof(EXTENSION)))
		so_exit_error("Wrong map extension.", 101);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd)
		so_exit_perror("Opening file failed", 102);
	return (fd);
}
