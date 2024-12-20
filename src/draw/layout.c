/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:16:43 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 10:05:28 by ipersids         ###   ########.fr       */
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
 * @return mlx_image_t** Array of pointers to the initialized layout images, 
 * 						 or NULL if initialization fails.
 */
mlx_image_t	**so_init_layout(t_game *g)
{
	int	i;

	i = 0;
	while (i < LAY_MAX)
	{
		if (WHITEGRND == i)
			g->layout[i] = so_new_image(g->mlx, g->m_width, g->m_height, 255);
		else
			g->layout[i] = so_new_image(g->mlx, g->m_width, g->m_height, 0);
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
