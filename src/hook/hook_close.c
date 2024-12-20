/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:41:18 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 23:42:37 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets the hook for the ESC key to close the game window.
 * 
 * This function checks if the ESC key is pressed. If it is, the function closes
 * the game window, destroys the game resources, and exits the program.
 * 
 * @param param Pointer to the game structure.
 */
void	so_set_esc_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		so_destroy_game(game);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @brief Sets the hook to close the game window.
 * 
 * This function is called when the game window is closed. It destroys the game
 * resources and exits the program.
 * 
 * @param param Pointer to the game structure.
 */
void	so_set_close_hook(void *param)
{
	t_game	*game;

	game = param;
	so_destroy_game(game);
	exit(EXIT_SUCCESS);
}
