/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:44 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/09 00:30:10 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** @note so_exit_error("Invalid map: the given map is empty.", 105); */

/* --------------------- Support function prototypes ----------------------- */

static char	**so_realloc_matrix(char **arr, size_t i, size_t *size, int fd);

/* ---------------------------- Implementation ----------------------------- */
/* ------------------- Support Function Implementation --------------------- */

char	**so_read_map(int fd)
{
	size_t	row;
	size_t	capacity;
	char	**matrix;
	char	*nl;

	row = 0;
	capacity = 10;
	matrix = (char **) malloc(capacity * sizeof(char *));
	if (!matrix)
	{
		close(fd);
		so_exit_perror("Map memory allocation failed", 110);
	}
	matrix[row] = get_next_line(fd, FALSE);
	while (matrix[row])
	{
		nl = ft_strchr(matrix[row], '\n');
		if (nl)
			*nl = '\0';
		if (++row >= capacity - 1)
			so_realloc_matrix(matrix, row, &capacity, fd);
		matrix[row] = get_next_line(fd, FALSE);
	}
	return (matrix);
}

static char	**so_realloc_matrix(char **arr, size_t i, size_t *size, int fd)
{
	char	**res;
	size_t	j;

	*size *= 2;
	res = (char **) malloc(*size * sizeof(char *));
	if (!res)
	{
		so_free_arr(arr, i);
		close(fd);
		so_exit_perror("Memory reallocation failed", 111);
	}
	j = 0;
	while (j < i)
	{
		res[j] = arr[j];
		j++;
	}
	so_free_arr(arr, i);
	return (res);
}
