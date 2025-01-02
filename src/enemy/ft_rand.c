/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:01:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/02 18:05:56 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Pseudo-random integer value
 */
int	ft_rand(void)
{
	static unsigned int	num = 21354676;

	num = (1103515245 * num + 12345) % RAND_MAX;
	return (num >> 24);
}
