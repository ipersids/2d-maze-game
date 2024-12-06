/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/05 14:25:29 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	mlx_t	*mlx;

	if (!is_args_valid(argc, argv))
		exit(-1);
	int fd = is_path_valid(argv[1]);
	if (!fd)
		exit(-2);
	ft_printf("File opened!\n");
	close(fd);
	mlx = mlx_init(WIDTH, HEIGHT, NAME, true);
	if (!mlx)
	{
		ft_printf("%s\n", mlx_strerror(mlx_errno));
		exit(-3);
	}
	mlx_texture_t* texture = mlx_load_png("textures/characters/yellow_character.png");
	if (!texture)
	{
		mlx_terminate(mlx);
		ft_printf("%s\n", mlx_strerror(mlx_errno));
		exit(-4);
	}
	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
	if (!img)
	{
		mlx_delete_texture(texture);
		mlx_terminate(mlx);
		ft_printf("%s\n", mlx_strerror(mlx_errno));
		exit(-5);
	}
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
	{
		mlx_delete_image(mlx, img);
		mlx_delete_texture(texture);
		mlx_terminate(mlx);
		ft_printf("%s\n", mlx_strerror(mlx_errno));
		exit(-6);
	}
	mlx_loop_hook(mlx, input_esc_hook, mlx);
	mlx_key_hook(mlx, input_move_hook, img);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (0);
}
