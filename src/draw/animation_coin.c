/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_coin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:40:34 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/21 22:30:52 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_coin_path(int32_t i_frame);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Loads the coin sprites for the animation.
 * 
 * @param game Pointer to the game structure.
 * @return mlx_image_t** Array of pointers to the loaded coin sprites, 
 * 						 or NULL if loading fails.
 */
mlx_image_t	**so_set_coin_animation(t_game *game)
{
	int32_t	i;

	i = 0;
	while (i < COIN_CNT)
	{
		game->coin->img[i] = so_load_sprite(get_coin_path(i), game->mlx, \
											game->sprite_size);
		if (!game->coin->img[i])
		{
			so_destroy_images(game->mlx, i, game->coin->img);
			return (NULL);
		}
		i++;
	}
	return (game->coin->img);
}

/**
 * @brief Draws the current frame of the coin animation at the given position.
 * 
 * @param game Pointer to the game structure.
 * @param x The x-coordinate where the animation frame should be drawn.
 * @param y The y-coordinate where the animation frame should be drawn.
 * @param type The layout type where the animation frame should be drawn.
 */
void	so_draw_anim(t_game *game, uint32_t x, uint32_t y, t_layout type)
{
	mlx_image_t	*dst;
	mlx_image_t	*src;

	dst = game->layout[type];
	src = game->coin->img[game->coin->curr_frame];
	so_draw_img(dst, src, x * game->sprite_size, y * game->sprite_size);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Gets the file path for a coin sprite based on its frame index.
 * 
 * @param i_frame The frame index of the coin sprite.
 * @return const char* The file path for the coin sprite.
 */
static const char	*get_coin_path(int32_t i_frame)
{
	static char	list[COIN_CNT][100] = {
		"textures/coins/Silver_11.png",
		"textures/coins/Silver_12.png",
		"textures/coins/Silver_13.png",
		"textures/coins/Silver_14.png",
		"textures/coins/Silver_15.png",
		"textures/coins/Silver_16.png",
		"textures/coins/Silver_17.png",
		"textures/coins/Silver_18.png",
		"textures/coins/Silver_19.png",
		"textures/coins/Silver_20.png"
	};

	return (list[i_frame]);
}
