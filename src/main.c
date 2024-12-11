/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/11 18:22:31 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* FOR TESTING */
int	main(int argc, char **argv) {
	t_map map;

	map.col = 0;
	map.exit = 0;
	map.item = 0;
	map.player = 0;
	map.row = 0;
	map.map_arr = NULL;
	so_validate_everything(argc, argv, &map);

	ft_printf("map.row = %d \nmap.col = %d\n", (int)map.row, (int)map.col);
	int32_t width = map.col * SPRITE_SIZE;
	int32_t height = map.row * SPRITE_SIZE;
	ft_printf("width = %d \nheight = %d\n", (int)width, (int)height);

	mlx_t *mlx = mlx_init(width, height, "Test background", true);
	if (!mlx)
	{
		so_free_arr(map.map_arr, map.row);
		mlx_strerror(mlx_errno);
		exit(-1);
	}
	

	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	mlx_image_t* img_background = mlx_new_image(mlx, width, height);
	ft_memset(img_background->pixels, 255, img_background->width * img_background->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img_background, 0, 0);

	mlx_texture_t* texture_free = mlx_load_png("textures/floor_plants.png");	
	mlx_image_t *img_free = mlx_texture_to_image(mlx, texture_free);
	mlx_delete_texture(texture_free);

	mlx_texture_t* texture_wall = mlx_load_png("textures/crate.png");	
	mlx_image_t *img_wall = mlx_texture_to_image(mlx, texture_wall);
	mlx_delete_texture(texture_wall);

	int32_t pos_x = 0;
	int32_t pos_y = 0;
	while (pos_x < (int32_t)map.col)
	{
		pos_y = 0;
		while (pos_y < (int32_t)map.row)
		{
			if (map.map_arr[pos_y][pos_x] == MAP_CODE[1])
				mlx_image_to_window(mlx, img_wall, pos_x * img_wall->height, pos_y * SPRITE_SIZE);
			else
				mlx_image_to_window(mlx, img_free, pos_x * img_free->height, pos_y * SPRITE_SIZE);
			pos_y++;
		}
		pos_x++;
	}

	mlx_loop(mlx);
	if (map.map_arr)
		so_free_arr(map.map_arr, map.row);
	mlx_terminate(mlx);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	mlx_t	*mlx;

// 	int fd = is_args_valid(argc, argv);
// 	ft_printf("File opened!\n");
// 	close(fd);
// 	mlx = mlx_init(WIDTH, HEIGHT, NAME, true);
// 	if (!mlx)
// 	{
// 		ft_printf("%s\n", mlx_strerror(mlx_errno));
// 		exit(-3);
// 	}
// 	mlx_texture_t* texture = mlx_load_png("textures/characters/yellow_character.png");
// 	if (!texture)
// 	{
// 		mlx_terminate(mlx);
// 		ft_printf("%s\n", mlx_strerror(mlx_errno));
// 		exit(-4);
// 	}
// 	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
// 	if (!img)
// 	{
// 		mlx_delete_texture(texture);
// 		mlx_terminate(mlx);
// 		ft_printf("%s\n", mlx_strerror(mlx_errno));
// 		exit(-5);
// 	}
// 	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
// 	{
// 		mlx_delete_image(mlx, img);
// 		mlx_delete_texture(texture);
// 		mlx_terminate(mlx);
// 		ft_printf("%s\n", mlx_strerror(mlx_errno));
// 		exit(-6);
// 	}
// 	mlx_loop_hook(mlx, input_esc_hook, mlx);
// 	mlx_key_hook(mlx, input_move_hook, img);
// 	mlx_loop(mlx);
// 	mlx_delete_image(mlx, img);
// 	mlx_delete_texture(texture);
// 	mlx_terminate(mlx);
// 	return (0);
// }
