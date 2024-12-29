/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:01:50 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/29 17:40:19 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_screen_path(int index);
static mlx_image_t	*resize_screen_img(t_game *game, mlx_image_t *img);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Loads the menu, lose and win screen images for the game.
 * 
 * @param game Pointer to the game structure.
 * @return mlx_image_t** Array of pointers to the loaded screen images, 
 * 						 or NULL if loading fails.
 */
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

/**
 * @brief Draws the source image centered on the destination image.
 * 
 * @param game Pointer to the game structure.
 * @param dest Pointer to the destination image.
 * @param src Pointer to the source image.
 */
void	so_draw_screen(t_game *game, mlx_image_t *dest, mlx_image_t *src)
{
	uint32_t	x_px;
	uint32_t	y_px;

	y_px = (game->height - src->height) / 2;
	x_px = (dest->width - src->width) / 2;
	so_draw_img(dest, src, x_px, y_px);
}

/* ------------------- Private Function Implementation --------------------- */
/**
 * @brief Gets the file path for a screen image based on its index.
 * 
 * @param index The index of the screen image.
 * @return const char* The file path for the screen image.
 */
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

/**
 * @brief Resizes the screen image to fit within the game window.
 * 
 * @param game Pointer to the game structure.
 * @param img Pointer to the image to be resized.
 * @return mlx_image_t* Pointer to the resized image.
 */
static mlx_image_t	*resize_screen_img(t_game *game, mlx_image_t *img)
{
	double		scale;
	uint32_t	_width;

	_width = game->width / 2;
	if (game->width + game->sprite_size <= img->width)
		_width = game->width - 10;
	if (_width > img->width * 2)
		_width = img->width * 2;
	scale = 1.0 * _width / img->width;
	if (!mlx_resize_image(img, img->width *scale, img->height *scale))
		return (NULL);
	return (img);
}
