/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:11:16 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 19:16:07 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Frees a dynamically allocated array of strings.
 * 
 * @param arr Pointer to the array of strings to be freed.
 * @param arr_size The number of elements in the array.
 */
void	so_free_arr(char **arr, size_t arr_size)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < arr_size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Frees a dynamically allocated array of MLX42 images.
 * 
 * @param mlx Pointer to the MLX42 instance.
 * @param i The number of images in the array.
 * @param images Array of pointers to the images to be deleted.
 * @return void* Always returns NULL.
 */
void	*so_destroy_images(mlx_t *mlx, int32_t i, mlx_image_t **images)
{
	int32_t	j;

	j = 0;
	while (j < i)
	{
		if (images[j])
		{
			mlx_delete_image(mlx, images[j]);
			images[j] = NULL;
		}
		j++;
	}
	return (NULL);
}

void	so_destroy_game(t_game *game)
{
	if (*game->layout)
		so_destroy_images(game->mlx, LAY_MAX, game->layout);
	if (game->coin)
		so_destroy_images(game->mlx, game->coin->cnt_frame, game->coin->img);
	if (game->player)
		mlx_delete_image(game->mlx, game->player);
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game->map->map_arr)
		so_free_arr(game->map->map_arr, game->map->row);
}
