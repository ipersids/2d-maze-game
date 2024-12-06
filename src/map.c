/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:44 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/06 10:38:46 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// typedef struct s_map
// {
// 	size_t		item;
// 	size_t		row;
// 	size_t		col;
// 	char		**map_arr;
// }				t_map;

static void	init_t_map(t_map *map, size_t capacity);

void	read_map(int fd)
{
	size_t	capacity;
	size_t	row;
}

static void	init_t_map(t_map *map, size_t capacity)
{
	map->col = 0;
	map->item = 0;
	map->row = 0;
	map->map_arr = (char **) malloc((capacity + 1) * sizeof(char *));
	if (!map->map_arr)
		exit(-1234);
}
