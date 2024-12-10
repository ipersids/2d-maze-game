/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:11:16 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/09 00:29:51 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	so_free_arr(char **arr, size_t arr_size)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < arr_size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
