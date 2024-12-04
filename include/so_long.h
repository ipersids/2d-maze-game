/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:52:27 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/04 15:42:19 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <fcntl.h>			// open
# include <unistd.h>		// close, read, write
# include <stdlib.h>		// malloc, free, exit
# include <stdio.h>			// perror
# include <string.h>		// strerror
// # include <math.h>		// math library


# ifndef WIDTH
#  define WIDTH 1366
# endif

# ifndef HEIGHT
#  define HEIGHT 768
# endif

# define NAME "So loooooooooooong game!"

void	input_key_hook(mlx_key_data_t keydata, void* param);
size_t	ft_putstrnl_fd(char *s, int fd);
size_t	ft_putunbr_fd(unsigned int n, int fd);

#endif