/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/31 02:47:23 by ipersids         ###   ########.fr       */
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
	if (!so_place_enemies(&game, &map))
	{
		so_destroy_game(&game);
		so_exit_error(ERR_SYSTEM);
	}
	if (!so_set_layout(&game) || !so_set_coin_animation(&game) \
		|| !so_set_num_animation(&game) || !so_get_screen_imgs(&game)
		|| !so_set_enemy_animation(&game))
	{
		so_destroy_game(&game);
		so_exit_error(ERR_MLX42);
	}
	so_general_loop_hook_init(&game);
	so_destroy_game(&game);
	return (0);
}
