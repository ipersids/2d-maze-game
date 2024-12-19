/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:11:16 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/19 16:28:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
