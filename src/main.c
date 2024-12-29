/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/29 17:46:29 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;

	if (2 != argc)
		so_exit_error(ERR_AGRC);
	so_map_init(&map);
	so_validate_level(argv[1], &map);
	so_game_init(&game, &map);
	so_mlx_init(&game);
	if (!so_set_layout(&game) || !so_set_coin_animation(&game) \
		|| !so_set_num_animation(&game) || !so_get_screen_imgs(&game))
	{
		so_destroy_game(&game);
		so_exit_error(ERR_MLX42);
	}
	mlx_loop_hook(game.mlx, so_set_screen_hook, &game);
	mlx_loop_hook(game.mlx, so_set_coin_hook, &game);
	mlx_loop_hook(game.mlx, so_set_counter_hook, &game);
	mlx_loop_hook(game.mlx, so_set_esc_hook, &game);
	mlx_close_hook(game.mlx, so_set_close_hook, &game);
	mlx_key_hook(game.mlx, so_set_move_hook, &game);
	mlx_loop(game.mlx);
	so_destroy_game(&game);
	return (0);
}
