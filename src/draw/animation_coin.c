/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_coin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:40:34 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 18:39:02 by ipersids         ###   ########.fr       */
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
	mlx_image_t	**ptr;

	ptr = so_get_imgarray(game, game->coin.img, COIN_CNT, get_coin_path);
	return (ptr);
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
