/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:11:16 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/01 21:40:16 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

uint32_t	**so_allocate_arr(int size1, int size2)
{
	int			i;
	uint32_t	**arr;

	arr = malloc(size1 * sizeof(uint32_t *));
	if (!arr)
		return (NULL);
	i = 0;
	while (size1 > i)
	{
		arr[i] = malloc(size2 * sizeof(uint32_t));
		if (!arr[i])
		{
			so_free_arr((void **)arr, i);
			return (NULL);
		}
		i++;
	}
	return (arr);
}

/**
 * @brief Frees a dynamically allocated array of strings.
 * 
 * @param arr Pointer to the array of strings to be freed.
 * @param arr_size The number of elements in the array.
 */
void	so_free_arr(void **arr, size_t arr_size)
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

/**
 * @brief Frees all resources associated with the game.
 * 
 * @param g Pointer to the game structure.
 */
void	so_destroy_game(t_game *g)
{
	if (g->layout[0])
		so_destroy_images(g->mlx, LAY_MAX, g->layout);
	if (g->src_img[0])
		so_destroy_images(g->mlx, BG_MAX, g->src_img);
	if (g->coin.img[0])
		so_destroy_images(g->mlx, g->coin.cnt_frame, g->coin.img);
	if (g->counter.img[0])
		so_destroy_images(g->mlx, g->counter.cnt_frame, g->counter.img);
	if (g->screen.img[0])
		so_destroy_images(g->mlx, g->screen.cnt_frame, g->screen.img);
	if (g->enemy.img[0])
		so_destroy_images(g->mlx, ENEMY_MAX_FRAMES, g->enemy.img);
	if (g->mlx)
		mlx_terminate(g->mlx);
	if (g->lvl.map)
		so_free_arr((void **)g->lvl.map, g->lvl.row);
	if (g->enemy.xyd)
		so_free_arr((void **)g->enemy.xyd, g->enemy.cnt);
}
