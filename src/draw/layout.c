/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:16:43 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/19 16:49:11 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

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
