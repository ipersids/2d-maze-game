/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:10:17 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/07 12:35:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	so_exit_error(const char *message, int exit_code)
{
	ft_printf("%sERROR%s -> %s\n", RED, DEFAULT, message);
	exit(exit_code);
}

void	so_exit_perror(const char *message, int exit_code)
{
	ft_printf("%sERROR%s -> ", RED, DEFAULT);
	perror(message);
	exit(exit_code);
}