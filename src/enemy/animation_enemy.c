/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_enemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:41:04 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/02 11:17:13 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_enemy_up_down_path(int32_t i_frame);
static const char	*get_enemy_left_right_path(int32_t i_frame);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets the enemy animation images.
 * 
 * This function loads the enemy animation images for up/down and left/right 
 * movements and stores them in the game's enemy image array. 
 * 
 * @param game Pointer to the game structure.
 * @return mlx_image_t** Array of pointers to the loaded enemy images, 
 * 						 or NULL if loading fails.
 */
mlx_image_t	**so_set_enemy_animation(t_game *game)
{
	if (!so_get_imgarray(game, game->enemy.img, ENEMY_ANIM_FRAMES * 2, \
						get_enemy_up_down_path))
		return (NULL);
	if (!so_get_imgarray(game, game->enemy.img + ENEMY_ANIM_FRAMES * 2, \
						ENEMY_ANIM_FRAMES * 2, get_enemy_left_right_path))
	{
		so_destroy_images(game->mlx, ENEMY_ANIM_FRAMES * 2, game->enemy.img);
		return (NULL);
	}
	return (game->enemy.img);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Gets the file path for an enemy up/down animation frame.
 * 
 * @param i_frame The frame index of the enemy animation.
 * @return const char* The file path for the enemy animation frame.
 */
static const char	*get_enemy_up_down_path(int32_t i_frame)
{
	static char	list[ENEMY_MAX_FRAMES][100] = {
		"textures/enemy/enemy-up-0.png",
		"textures/enemy/enemy-up-1.png",
		"textures/enemy/enemy-up-2.png",
		"textures/enemy/enemy-up-3.png",
		"textures/enemy/enemy-up-4.png",
		"textures/enemy/enemy-up-5.png",
		"textures/enemy/enemy-up-6.png",
		"textures/enemy/enemy-up-7.png",
		"textures/enemy/enemy-down-0.png",
		"textures/enemy/enemy-down-1.png",
		"textures/enemy/enemy-down-2.png",
		"textures/enemy/enemy-down-3.png",
		"textures/enemy/enemy-down-4.png",
		"textures/enemy/enemy-down-5.png",
		"textures/enemy/enemy-down-6.png",
		"textures/enemy/enemy-down-7.png"
	};

	return (list[i_frame]);
}

/**
 * @brief Gets the file path for an enemy left/right animation frame.
 * 
 * @param i_frame The frame index of the enemy animation.
 * @return const char* The file path for the enemy animation frame.
 */
static const char	*get_enemy_left_right_path(int32_t i_frame)
{
	static char	list[ENEMY_MAX_FRAMES][100] = {
		"textures/enemy/enemy-left-0.png",
		"textures/enemy/enemy-left-1.png",
		"textures/enemy/enemy-left-2.png",
		"textures/enemy/enemy-left-3.png",
		"textures/enemy/enemy-left-4.png",
		"textures/enemy/enemy-left-5.png",
		"textures/enemy/enemy-left-6.png",
		"textures/enemy/enemy-left-7.png",
		"textures/enemy/enemy-right-0.png",
		"textures/enemy/enemy-right-1.png",
		"textures/enemy/enemy-right-2.png",
		"textures/enemy/enemy-right-3.png",
		"textures/enemy/enemy-right-4.png",
		"textures/enemy/enemy-right-5.png",
		"textures/enemy/enemy-right-6.png",
		"textures/enemy/enemy-right-7.png"
	};

	return (list[i_frame]);
}
