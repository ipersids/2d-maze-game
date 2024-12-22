/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:51:32 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 01:07:57 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Checks if the path to the map is valid.
 * 
 * This function validates the the map have `.ber` file extension 
 * and the file can be opened. It sets the file descriptor if the file
 * is valid.
 * 
 * @param path The file path to the map.
 * @param fd Pointer to the file descriptor.
 * @return int 0 if the path is valid, otherwise an error code.
 */
int	so_validate_path(char *path, int *fd)
{
	size_t	i;

	i = ft_strlen(path) - ft_strlen(EXTENSION);
	if (0 > i || ft_memcmp(&(path[i]), &EXTENSION, sizeof(EXTENSION)))
		return (ERR_EXTENSION);
	*fd = open(path, O_RDONLY);
	if (-1 == *fd)
		return (ERR_SYSTEM);
	return (0);
}
