/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 00:07:28 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/01 18:54:47 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	so_general_loop_hook_init(t_game *game)
{
	mlx_loop_hook(game->mlx, so_set_screen_hook, game);
	mlx_loop_hook(game->mlx, so_set_coin_hook, game);
	mlx_loop_hook(game->mlx, so_set_counter_hook, game);
	mlx_loop_hook(game->mlx, so_set_enemy_hook, game);
	mlx_loop_hook(game->mlx, so_set_esc_hook, game);
	mlx_close_hook(game->mlx, so_set_close_hook, game);
	mlx_key_hook(game->mlx, so_set_move_hook, game);
	mlx_loop(game->mlx);
}
