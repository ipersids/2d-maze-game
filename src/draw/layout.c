/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:16:43 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 16:23:28 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes the layout images for the game.
 * 
 * This function creates new images for each layout type (foreground, 
 * background, white background). It sets the pixel values for the white 
 * background to 255 (fully opaque) and for other backgrounds to 0 
 * (fully transparent). Then it calls so_draw_background() to draw the map on
 * transparent background. If any image creation fails, it cleans up
 * and returns NULL.
 * 
 * @param g Pointer to the game structure.
 * @return mlx_image_t** Array of pointers to the set layout images, 
 * 						 or NULL if creation fails.
 */
mlx_image_t	**so_set_layout(t_game *g)
{
	int	i;
	int	_height;

	i = 0;
	_height = g->height + g->sprite_size;
	while (i < LAY_MAX)
	{
		if (WHITEGRND == i)
			g->layout[i] = so_new_image(g->mlx, g->width, _height, 255);
		else
			g->layout[i] = so_new_image(g->mlx, g->width, _height, 0);
		if (!g->layout[i])
		{
			so_destroy_images(g->mlx, i, g->layout);
			return (NULL);
		}
		i++;
	}
	if (!so_draw_background(g))
	{
		so_destroy_images(g->mlx, LAY_MAX, g->layout);
		return (NULL);
	}
	return (g->layout);
}

/**
 * @brief Cleans the specified layout by setting all its pixels to 0.
 * 
 * @param game Pointer to the game structure.
 * @param type The layout type to be cleaned.
 */
void	so_clean_layout(t_game *game, t_layout type)
{
	mlx_image_t	*layout;

	layout = game->layout[type];
	ft_memset(layout->pixels, 0, layout->width * layout->height * RGBA);
}
