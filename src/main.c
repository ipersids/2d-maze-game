/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/09 00:34:09 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* FOR TESTING */
int	main(int argc, char **argv)
{
	t_map mapmap;

	int fd = is_args_valid(argc, argv);
	ft_printf("File opened!\n");

	char **map = so_read_map(fd);
	ft_printf("\nMap is loaded!\n");
	close(fd);

	size_t i = 0;
	for ( ; map[i] != NULL; i++) {
		ft_printf("%s\n", map[i]);
	}
	ft_printf("\n<<< END OF MAP\n");

	mapmap.col = ft_strlen(map[0]);
	mapmap.row = i;
	mapmap.exit = 0;
	mapmap.item = 0;
	mapmap.player = 0;
	mapmap.map_arr = map;
	i = 0;
	ft_printf("\nValidating the map content:\n");
	for ( ; map[i] != NULL; i++) {
		ft_printf("line [%d] [ p = %p ]:", (int)i + 1, map[i]);
		is_line_valid(&mapmap, i);
		ft_printf("%s checked %s\n", YELLOW, DEFAULT);
	}
	ft_printf("%s\nRESULT%s >>> ", YELLOW, DEFAULT);
	is_map_valid(&mapmap);
	ft_printf("%sMap is valid.%s\n", GREEN, DEFAULT);

	if (mapmap.map_arr)
		so_free_arr(map, i);
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
