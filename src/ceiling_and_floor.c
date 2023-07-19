/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_and_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 00:41:05 by sreinhol          #+#    #+#             */
/*   Updated: 2023/07/19 18:40:07 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	floor_color(t_data *data)
{
	int	i;
	int	j;
	int	floor;

	floor = (int)data->floor_color;
	i = 0;
	while (i < S_WIDTH)
	{
		j = S_HEIGHT / 2;
		while (j < S_HEIGHT)
		{
			data->buffer[j][i] = floor;
			j++;
		}
		i++;
	}
}

void	ceiling_floor_color(t_data *data)
{
	int	i;
	int	j;
	int	ceiling;

	ceiling = (int)data->ceiling_color;
	i = 0;
	while (i < S_WIDTH)
	{
		j = 0;
		while (j < S_HEIGHT) // galiba S_HEIGHT/2 yapsak daha iyi olur
		{
			data->buffer[j][i] = ceiling;
			j++;
		}
		i++;
	}
	floor_color(data);
}
