/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:41:18 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 18:59:24 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

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

void	so_set_close_hook(void *param)
{
	t_game	*game;
	
	game = param;
	so_destroy_game(game);
	exit(EXIT_SUCCESS);
}
