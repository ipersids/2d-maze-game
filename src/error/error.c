/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:10:17 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 01:23:39 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static char	*get_error_message(int exit_code);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Prints an error message and exits the program with the given code.
 * 
 * This function prints an error message based on the exit code and exits 
 * the program. It handles system errors, MLX42 errors, 
 * and custom error messages.
 * 
 * @param exit_code The exit code indicating the type of error.
 */
void	so_exit_error(int exit_code)
{
	ft_printf("%sERROR (%d)%s -> ", RED, exit_code, DEFAULT);
	if (ERR_SYSTEM == exit_code)
		ft_printf("system: %s\n", strerror(errno));
	else if (ERR_MLX42 == exit_code)
		ft_printf("MLX42: %s\n", mlx_strerror(mlx_errno));
	else
		ft_printf("%s\n", get_error_message(exit_code));
	exit(exit_code);
}

/**
 * @brief Prints an error message.
 * 
 * This function prints an error message based on the  code.
 * It handles system errors, MLX42 errors, and custom error messages.
 * 
 * @param exit_code The exit code indicating the type of error.
 */
void	so_print_error(int exit_code)
{
	ft_printf("%sERROR (%d)%s -> ", RED, exit_code, DEFAULT);
	if (ERR_SYSTEM == exit_code)
		ft_printf("system: %s\n", strerror(errno));
	else if (ERR_MLX42 == exit_code)
		ft_printf("MLX42: %s\n", mlx_strerror(mlx_errno));
	else
		ft_printf("%s\n", get_error_message(exit_code));
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Returns a custom error message based on the exit code.
 * 
 * @param exit_code The exit code indicating the type of error.
 * @return char* The error message corresponding to the exit code.
 */
static char	*get_error_message(int exit_code)
{
	static char	list[11][100] = {
		"Usage: ./so_long path/map.ber",
		"Wrong map extension.",
		"Invalid map: check forbidden characters.",
		"Invalid map: check the number of columns.",
		"Invalid map: the given map is empty.",
		"Invalid map: wrong amount of players.",
		"Invalid map: wrong amount of exits.",
		"Invalid map: no one collectible found.",
		"Invalid map: it isn't surrounded by walls.",
		"The map doesn't fit the maximum monitor size.",
		"Invalid map: there is no way to win"
	};

	if (!(ERR_MLX42 < exit_code && ERR_MAX > exit_code))
		return ("Uknown error code.");
	return (list[exit_code % 100]);
}
