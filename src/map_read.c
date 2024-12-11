/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:44 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/11 15:31:17 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** @note so_exit_error("Invalid map: the given map is empty.", 105); */

/* --------------------- Support function prototypes ----------------------- */

static char	**so_realloc_matrix(char **arr, size_t i, size_t *size);

/* ---------------------------- Implementation ----------------------------- */

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
		return (NULL);
	matrix[row] = get_next_line(fd, FALSE);
	while (matrix[row])
	{
		nl = ft_strchr(matrix[row++], '\n');
		if (nl)
			*nl = '\0';
		if (row >= capacity)
		{
			matrix = so_realloc_matrix(matrix, row, &capacity);
			if (!matrix)
				return (NULL);
		}
		matrix[row] = get_next_line(fd, FALSE);
	}
	return (matrix);
}

/* ------------------- Support Function Implementation --------------------- */

static char	**so_realloc_matrix(char **arr, size_t i, size_t *size)
{
	char	**res;
	size_t	j;

	*size = *size * 2;
	res = (char **) malloc(*size * sizeof(char *));
	if (!res)
	{
		so_free_arr(arr, i);
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		res[j] = arr[j];
		j++;
	}
	free(arr);
	return (res);
}
