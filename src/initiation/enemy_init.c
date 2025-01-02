/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:39:55 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/30 21:55:45 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes the enemy structure with default values.
 * 
 * @param enemy Pointer to the enemy structure.
 * @param cnt_frame Number of frames in the animation (one direction).
 * @param speed Speed of the animation.
 */
void	so_enemy_init(t_enemy *enemy, int cnt_frame, double speed)
{
	enemy->img[0] = NULL;
	enemy->curr_frame = 0;
	enemy->cnt_frame = cnt_frame;
	enemy->elapsed_time = 0;
	enemy->speed = speed;
	enemy->fps = 1.0 / (speed * cnt_frame);
	enemy->xyd = NULL;
	enemy->cnt = 0;
}
