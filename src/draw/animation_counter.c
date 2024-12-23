/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:13:03 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 19:33:28 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_number_path(int index);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Loads the number sprites for the animation.
 * 
 * @param game Pointer to the game structure.
 * @return mlx_image_t** Array of pointers to the loaded number sprites, 
 * 						 or NULL if loading fails.
 */
mlx_image_t	**so_set_num_animation(t_game *game)
{
	mlx_image_t	**ptr;

	ptr = so_get_imgarray(game, game->counter.img, NUM_CNT, get_number_path);
	return (ptr);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Gets the file path for a number sprite based on its frame index.
 * 
 * @param i_frame The frame index of the number sprite.
 * @return const char* The file path for the number sprite.
 */
static const char	*get_number_path(int index)
{
	static char	list[NUM_CNT][100] = {
		"textures/kenney/numbers/ui_num0.png",
		"textures/kenney/numbers/ui_num1.png",
		"textures/kenney/numbers/ui_num2.png",
		"textures/kenney/numbers/ui_num3.png",
		"textures/kenney/numbers/ui_num4.png",
		"textures/kenney/numbers/ui_num5.png",
		"textures/kenney/numbers/ui_num6.png",
		"textures/kenney/numbers/ui_num7.png",
		"textures/kenney/numbers/ui_num8.png",
		"textures/kenney/numbers/ui_num9.png",
	};

	if (0 > index || NUM_CNT <= index)
		index = 0;
	return (list[index]);
}
