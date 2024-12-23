/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_anim_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:47:11 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 19:43:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static void	get_array_of_nmb(int n, int *arr, int arr_len);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets the hook for updating the move counter animation.
 * 
 * This function updates the move counter animation based on the player's 
 * move count. It converts the move count to an array of digits and draws 
 * the corresponding images on the foreground layout.
 * 
 * @param param Pointer to the game structure.
 */
void	so_set_counter_hook(void *param)
{
	int		arr[NUM_ARR_SIZE];
	int		i;
	int		size;
	t_game	*g;

	g = param;
	i = 0;
	size = NUM_ARR_SIZE;
	if (g->lvl.col < size)
		size = size / 2;
	get_array_of_nmb(g->pl.move_cnt, arr, size);
	while (i < size)
	{
		so_draw_img(g->layout[FOREGRND], g->counter.img[arr[i]], \
					((g->lvl.col - size) / 2 + i) * g->sprite_size, \
					g->height - g->sprite_size * 1.5);
		i++;
	}
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Converts a number to an array of its digits.
 * 
 * @param n The number to be converted.
 * @param arr Pointer to the array to store the digits.
 * @param arr_len The length of the array.
 */
static void	get_array_of_nmb(int n, int *arr, int arr_len)
{
	while (n > 0 && arr_len >= 0)
	{
		arr_len--;
		arr[arr_len] = n % 10;
		n /= 10;
	}
	while (arr_len >= 0)
	{
		arr_len--;
		arr[arr_len] = 0;
	}
}
