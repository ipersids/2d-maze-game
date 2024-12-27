/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:01:50 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/27 17:04:06 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_screen_path(int index);
static mlx_image_t	*resize_screen_img(t_game *game, mlx_image_t *img);

/* --------------------------- Public Functions ---------------------------- */

mlx_image_t	**so_get_screen_imgs(t_game *game)
{
	int				i;
	mlx_texture_t	*texture;

	i = 0;
	while (i < SCREEN_MAX)
	{
		texture = mlx_load_png(get_screen_path(i));
		if (!texture)
			return (NULL);
		game->screen.img[i] = mlx_texture_to_image(game->mlx, texture);
		mlx_delete_texture(texture);
		if (!game->screen.img[i])
		{
			so_destroy_images(game->mlx, i, game->screen.img);
			return (NULL);
		}
		resize_screen_img(game, game->screen.img[i]);
		i++;
	}
	return (game->screen.img);
}

void	so_draw_screen(t_game *game, mlx_image_t *dest, mlx_image_t *src)
{
	uint32_t	x_px;
	uint32_t	y_px;

	y_px = (game->height - src->height) / 2;
	x_px = (dest->width - src->width) / 2;
	so_draw_img(dest, src, x_px, y_px);
}

/* ------------------- Private Function Implementation --------------------- */

static const char	*get_screen_path(int index)
{
	static char	list[SCREEN_MAX][100] = {
		"textures/other/pixil-frame-menu-green.png",
		"textures/other/pixil-frame-menu-red.png",
		"textures/other/pixil-frame-menu-yellow.png",
		"textures/other/pixil-frame-win.png",
		"textures/other/pixil-frame-lose.png"
	};

	return (list[index]);
}

static mlx_image_t	*resize_screen_img(t_game *game, mlx_image_t *img)
{
	uint32_t	nwidth;
	uint32_t	nheight;

	nwidth = game->width / 2;
	nheight = game->sprite_size * 3;
	if (game->width + game->sprite_size <= img->width)
		nwidth = game->width - 10;
	if (nwidth > img->width * 2)
		nwidth = img->width * 2;
	if (!mlx_resize_image(img, nwidth, nheight))
		return (NULL);
	return (img);
}
