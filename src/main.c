/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/20 00:04:44 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	so_game_init(&game, &map);
	so_validate_everything(argc, argv, game.map);
	so_mlx_init(&game);
	if (!so_init_layout(&game))
	{
		so_free_arr(map.map_arr, map.row);
		return(123);
	}
	/// TESTING >>>
	printf("1\n");
	mlx_image_to_window(game.mlx, game.layout[WHITEGRND], 0, 0);
	printf("2\n");
	mlx_image_to_window(game.mlx, game.layout[BACKGRND], 0, 0);
	printf("3\n");
	mlx_image_to_window(game.mlx, game.layout[FOREGRND], 0, 0);
	printf("4\n");
	mlx_loop(game.mlx);
	/// TESTING END <<<

	// mlx_terminate(game.mlx);
	so_free_arr(map.map_arr, map.row);
	return (0);
}
