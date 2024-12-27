/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/27 15:56:57 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;
	int		check;

	if (2 != argc)
		so_exit_error(ERR_AGRC);

	so_map_init(&map);
	check = so_validate_level(argv[1], &map);
	if (check)
		so_exit_error(check);
	so_game_init(&game, &map);

	so_mlx_init(&game);
	if (!so_set_layout(&game))
	{
		so_destroy_game(&game);
		return(123);
	}
	/// TESTING >>>
	mlx_image_to_window(game.mlx, game.layout[WHITEGRND], 0, 0);
	mlx_image_to_window(game.mlx, game.layout[BACKGRND], 0, 0);
	mlx_image_to_window(game.mlx, game.layout[ENEMYGRND], 0, 0);
	mlx_image_to_window(game.mlx, game.layout[FOREGRND], 0, 0);

	if (!so_set_coin_animation(&game))
	{
		so_destroy_game(&game);
		return -1;
	}

	if (!so_set_num_animation(&game))
	{
		so_destroy_game(&game);
		return -1;
	}

	if (!so_get_screen_imgs(&game))
	{
		so_destroy_game(&game);
		return -1;
	}

	mlx_loop_hook(game.mlx, so_set_menu_hook, &game);
	mlx_loop_hook(game.mlx, so_set_coin_hook, &game);
	mlx_loop_hook(game.mlx, so_set_counter_hook, &game);
	mlx_loop_hook(game.mlx, so_set_esc_hook, &game);
	mlx_close_hook(game.mlx, so_set_close_hook, &game);
	mlx_key_hook(game.mlx, so_set_move_hook, &game);
	/// TESTING END <<<

	mlx_loop(game.mlx);
	so_destroy_game(&game);
	return (0);
}
