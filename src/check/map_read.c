/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:44 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 15:21:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static char	**so_realloc_matrix(char **arr, int32_t i, int32_t *size);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Read the map from a file descriptor and allocate memory for a matrix.
 * 
 * @param fd File descriptor to read the map from.
 * @return char** Pointer to the dynamically allocated matrix of map, 
 * 				  or NULL if an error occurs.
 */
char	**so_read_map(int fd)
{
	int32_t	row;
	int32_t	capacity;
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

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Reallocates the matrix to a larger size.
 * 
 * This function reallocates the given matrix to a new size that is double the 
 * current size. It copies the existing elements to the new matrix and frees 
 * the old matrix.
 * 
 * @param arr Pointer to the current matrix.
 * @param i Current number of rows in the matrix.
 * @param size Pointer to the current size of the matrix, which will be updated.
 * @return char** Pointer to the reallocated matrix, or NULL if an error occurs.
 */
static char	**so_realloc_matrix(char **arr, int32_t i, int32_t *size)
{
	char	**res;
	int32_t	j;

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
