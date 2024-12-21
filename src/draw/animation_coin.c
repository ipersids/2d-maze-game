/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_coin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:40:34 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/21 18:57:39 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_coin_path(int32_t i_frame);

/* --------------------------- Public Functions ---------------------------- */

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

void so_draw_anim(t_game *game, uint32_t x, uint32_t y, t_layout type)
{
	mlx_image_t	*dst;
	mlx_image_t	*src;

	dst = game->layout[type];
	src = game->coin->img[game->coin->curr_frame];
	so_draw_img(dst, src, x * game->sprite_size, y * game->sprite_size);
}

/* ------------------- Private Function Implementation --------------------- */

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
