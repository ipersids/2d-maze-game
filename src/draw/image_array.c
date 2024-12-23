/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:17:11 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 12:41:59 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Loads an array of images using the provided path function.
 * 
 * This function loads an array of images using the provided path function and
 * stores them in the images array. If any image fails to load, it cleans up
 * and returns NULL.
 * 
 * @param g Pointer to the game structure.
 * @param images Array of pointers to store the loaded images.
 * @param cnt The number of images to load.
 * @param get_path Function pointer to get the file path for each image.
 * @return mlx_image_t** Array of pointers to the loaded images, 
 * 						 or NULL if loading fails.
 */
mlx_image_t	**so_get_imgarray(t_game *g, mlx_image_t **images, int cnt, \
								const char *(*get_path)(int))
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		images[i] = so_load_sprite(get_path(i), g->mlx, g->sprite_size);
		if (!images[i])
		{
			so_destroy_images(g->mlx, i, images);
			return (NULL);
		}
		i++;
	}
	return (images);
}
