/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:45:19 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 10:21:35 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Loads a sprite from a PNG file and resizes it if necessary.
 * 
 * @param path The file path to the PNG image.
 * @param mlx Pointer to the MLX42 instance.
 * @param sprite_size The size of the sprite.
 * @return mlx_image_t* Pointer to the loaded and resized sprite image, 
 * 						or NULL if loading or resizing fails.
 */
mlx_image_t	*so_load_sprite(const char *path, mlx_t *mlx, uint32_t sprite_size)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_printf("MLX42: %s\n", mlx_strerror(mlx_errno));
		return (NULL);
	}
	img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
	{
		ft_printf("MLX42: %s\n", mlx_strerror(mlx_errno));
		return (NULL);
	}
	if (!mlx_resize_image(img, sprite_size, sprite_size))
	{
		ft_printf("MLX42: %s\n", mlx_strerror(mlx_errno));
		return (NULL);
	}
	return (img);
}
