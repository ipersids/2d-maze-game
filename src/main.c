/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/21 22:50:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_test_main
{
	t_game	g;
	t_map	map;
	t_anim	coin;
} t_test_main;

int	main(int argc, char **argv)
{
	t_test_main t;

	so_game_init(&t.g, &t.map, &t.coin);
	so_validate_everything(argc, argv, t.g.map);
	so_mlx_init(&t.g);
	if (!so_set_layout(&t.g))
	{
		so_free_arr(t.map.map_arr, t.map.row);
		return(123);
	}
	/// TESTING >>>
	mlx_image_to_window(t.g.mlx, t.g.layout[WHITEGRND], 0, 0);
	mlx_image_to_window(t.g.mlx, t.g.layout[BACKGRND], 0, 0);
	mlx_image_to_window(t.g.mlx, t.g.layout[FOREGRND], 0, 0);

	t.g.player = so_load_sprite(
		"textures/kenney/characters/yellow_character.png", \
		t.g.mlx, t.g.sprite_size \
	);
	if (!t.g.player)
	{
		mlx_terminate(t.g.mlx);
		so_free_arr(t.map.map_arr, t.map.row);
		return -1;
	}
	mlx_image_to_window(t.g.mlx, t.g.player, t.g.map->p_xy[Y] * t.g.sprite_size, t.g.map->p_xy[X] * t.g.sprite_size);

	if (!so_set_coin_animation(&t.g))
	{
		printf("free\n");
		so_destroy_game(&t.g);
		return -1;
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop_hook(t.g.mlx, so_set_coin_hook, &t.g);
	mlx_loop_hook(t.g.mlx, so_set_esc_hook, &t.g);
	mlx_close_hook(t.g.mlx, so_set_close_hook, &t.g);
	mlx_key_hook(t.g.mlx, so_set_move_hook, &t.g);
	/// TESTING END <<<

	mlx_loop(t.g.mlx);
	so_destroy_game(&t.g);
	return (0);
}
