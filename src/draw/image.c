/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:41:37 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/17 23:13:34 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static uint32_t	get_rgba(int r, int g, int b, int a);
static int		is_px_place_valid(mlx_image_t *img, uint32_t x, uint32_t y);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Draw the pixels of source image to the specific place of destination.
 * 
 * @param dest pointer to the destination MLX42 image
 * @param s pointer to the source MLX42 image
 * @param x x-axis position where the `s` will be drawn on the `dest` image
 * @param y y-axis position where the `s` will be drawn on the `dest` image
 */
void	so_draw_img(mlx_image_t *dest, mlx_image_t *s, uint32_t x, uint32_t y)
{
	uint32_t	px_color;
	uint32_t	src_x;
	uint32_t	src_y;

	src_x = 0;
	while (src_x < s->width)
	{
		src_y = 0;
		while (src_y < s->height)
		{
			px_color = so_get_pixel(s, src_x, src_y);
			if (px_color && is_px_place_valid(dest, x + src_x, y + src_y))
				mlx_put_pixel(dest, x + src_x, y + src_y, px_color);
			src_y++;
		}
		src_x++;
	}
}

/**
 * @brief Get the single pixel (rgba) as an integer from image.
 * 
 * @param img pointer to MLX42 image 
 * @param px_x x-axis position to find pixel
 * @param px_y y-axis position to find pixel
 * @return int32_t encoded pixel
 */
uint32_t	so_get_pixel(mlx_image_t *img, uint32_t px_x, uint32_t px_y)
{
	uint32_t	rgba;
	uint8_t		*channel;

	if (px_x > img->width || px_y > img->height)
		return (0x00000000);
	channel = img->pixels + (px_y * img->width + px_x) * RGBA;
	rgba = get_rgba(*(channel), *(channel + 1), *(channel + 2), *(channel + 3));
	return (rgba);
}

/**
 * @brief Creates a new image with specified dimensions and 
 * 		  initializes its pixels.
 * 
 * This function creates a new image using the MLX42 library with the specified 
 * width and height. It then initializes the image's pixels with the provided 
 * channel value.
 * 
 * @param mlx Pointer to the MLX42 window.
 * @param w Width of the new image.
 * @param h Height of the new image.
 * @param channel Value to initialize the image's pixels with.
 * @return mlx_image_t* Pointer to the newly created image, 
 * 						or NULL if creation fails.
 */
mlx_image_t	*so_new_image(mlx_t *mlx, uint32_t w, uint32_t h, uint8_t *channel)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, w, h);
	if (!img)
		return (NULL);
	ft_memset(img->pixels, channel, w * h * RGBA);
	return (img);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Encode four individual bytes into the rgba (int).
 * 
 * A function that combines four individual channel bytes into a single 
 * integer using bit-shifting operations.
 * 
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param a alpha channel (transparency)
 * @return int the rgba channels.
 */
static uint32_t	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/**
 * @brief Check pixel is out of image bounds
 * 
 * @param img pointer to MLX42 image 
 * @param x x-axis (column) position
 * @param y y-axis (row) position
 * @return int 
 */
static int	is_px_place_valid(mlx_image_t *img, uint32_t x, uint32_t y)
{
	return (x < img->width && y < img->height);
}
