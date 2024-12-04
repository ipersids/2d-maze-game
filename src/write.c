/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:26:50 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/04 15:42:04 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Outputs a string to the specified file descriptor.
 * 
 * This function writes the string `s` to the given file descriptor `fd`.
 * 
 * @param s The string to output.
 * @param fd The file descriptor to which the string is written.
 * 
 * @return size_t Number of characters that are written.
 */
size_t	ft_putstrnl_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return (write(fd, "(null)", 6));
	len = 0;
	while (s[len] != '\0')
		len++;
	len = write(fd, s, len);
	len += write(1, "\n", 1);
	return (len);
}

/**
 * @brief Outputs an unsigned integer to the specified file descriptor.
 * 
 * This function writes the unsigned integer `n` 
 * to the given file descriptor `fd`.
 * 
 * @param n The unsigned integer to output.
 * @param fd The file descriptor to which the integer is written.
 * 
 * @return size_t Number of characters that are written.
 */
size_t	ft_putunbr_fd(unsigned int n, int fd)
{
	char	ch;
	size_t	len;

	len = 0;
	ch = '0';
	if (n > 9)
		len += ft_putunbr_fd(n / 10, fd);
	ch = ch + (n % 10);
	len += write(fd, &ch, 1);
	return (len);
}
