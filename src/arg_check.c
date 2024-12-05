/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:51:32 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/05 17:44:05 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_args_valid(int argc, char **argv)
{
	size_t	i;
	size_t	j;

	if (2 != argc)
	{
		ft_printf("Usage: ./so_long path/map.ber\n");
		return (0);
	}
	i = ft_strlen(argv[1]) - ft_strlen(MAP_EXTENSION);
	j = 0;
	while ('\0' != argv[1][i])
	{
		if (0 == i || argv[1][i++] != MAP_EXTENSION[j++])
		{
			ft_printf("Map extention should be %s\n", MAP_EXTENSION);
			return (0);
		}
	}
	return (1);
}

int	is_path_valid(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (-1 == fd)
	{
		perror("Opening file failed");
		return (0);
	}
	return (fd);
}
