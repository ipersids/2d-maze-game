/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:43:51 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/10 01:57:20 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	so_validate_argv(int argc, char **argv, int *fd);
static void	so_validate_map_lines(t_map *map);

void	so_validate_everything(int argc, char **argv, t_map *map)
{
	int	fd;
	int	check;

	so_validate_argv(argc, argv, &fd);
	map->map_arr = so_read_map(fd);
	close(fd);
	if (!map->map_arr)
		so_exit_perror("Memory allocation failed", 110);
	if (!map->map_arr[0])
	{
		free(map->map_arr);
		so_exit_error("Invalid map: the given map is empty.", 105);
	}
	so_validate_map_lines(map);
	check = is_map_valid(map);
	if (check)
	{
		so_free_arr(map->map_arr, map->row);
		exit(check);
	}
	ft_printf("%sMap is valid.%s\n", GREEN, DEFAULT);
}

static void	so_validate_map_lines(t_map *map)
{
	int		check;
	size_t	i;

	i = 0;
	map->col = ft_strlen(map->map_arr[0]);
	while (map->map_arr[map->row] != NULL)
		map->row++;
	while (map->map_arr[i] != NULL)
	{
		check = is_line_valid(map, i);
		if (check)
		{
			so_free_arr(map->map_arr, map->row);
			exit(check);
		}
		i++;
	}
}

static void	so_validate_argv(int argc, char **argv, int *fd)
{
	int	check;

	check = is_args_valid(argc, argv);
	if (check)
		exit(check);
	*fd = open(argv[1], O_RDONLY);
	if (-1 == *fd)
	{
		so_print_perror("Opening file failed", 102);
		exit(102);
	}
}
