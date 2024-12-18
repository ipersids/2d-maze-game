/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/18 19:55:29 by ipersids         ###   ########.fr       */
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

	/// TESTING >>>
	printf("MAIN: \n");
	printf("sprite_size [%u] * game.map->row [%zu] = %d\n", game.spite_size, game.map->row, game.m_height);
	printf("sprite_size [%u] * game.map->col [%zu] = %d\n", game.spite_size, game.map->col, game.m_width);
	
	mlx_image_t* img_background = mlx_new_image(game.mlx, game.mlx->width, game.mlx->height);
	ft_memset(img_background->pixels, 255, game.mlx->width * game.mlx->height * sizeof(int32_t));
	mlx_image_to_window(game.mlx, img_background, 0, 0);
	printf("game.mlx->width: %d\n", game.mlx->width);
	printf("game.mlx->height: %d\n", game.mlx->height);

	mlx_texture_t* texture_free = mlx_load_png("textures/kenney/background/floor_free_plants.png");	
	mlx_image_t *img_free = mlx_texture_to_image(game.mlx, texture_free);
	mlx_resize_image(img_free, game.spite_size, game.spite_size);
	mlx_delete_texture(texture_free);

	mlx_texture_t* texture_wall = mlx_load_png("textures/kenney/background/floor_wall_tree.png");	
	mlx_image_t *img_wall = mlx_texture_to_image(game.mlx, texture_wall);
	mlx_resize_image(img_wall, game.spite_size, game.spite_size);
	mlx_delete_texture(texture_wall);

	int32_t pos_x = 0;
	int32_t pos_y = 0;
	while (pos_x < (int32_t)map.col)
	{
		pos_y = 0;
		while (pos_y < (int32_t)map.row)
		{
			if (map.map_arr[pos_y][pos_x] == MAP_CODE[1])
				mlx_image_to_window(game.mlx, img_wall, pos_x * game.spite_size, pos_y * game.spite_size);
			else
				mlx_image_to_window(game.mlx, img_free, pos_x * game.spite_size, pos_y * game.spite_size);
			pos_y++;
		}
		pos_x++;
	}
	mlx_loop(game.mlx);
	/// TESTING END <<<

	// mlx_terminate(game.mlx);
	so_free_arr(map.map_arr, map.row);
	return (0);
}
