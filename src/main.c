/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/09 17:34:11 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* FOR TESTING */
int	main(int argc, char **argv)
{
	t_map map;

	map.col = 0;
	map.exit = 0;
	map.item = 0;
	map.player = 0;
	map.row = 0;
	map.map_arr = NULL;
	so_validate_everything(argc, argv, &map);

	if (map.map_arr)
		so_free_arr(map.map_arr, map.row);
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
