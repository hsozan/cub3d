/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:13:54 by sreinhol          #+#    #+#             */
/*   Updated: 2023/07/22 17:50:54 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
/*
static void	check_map_helper(t_check *check, t_data *data, int i, int j)
{
	char	**map;

	map = data->map.map_array;
	if (map[j][i] != '1' && map[j][i] != '0'
	&& map[j][i] != '\n' && map[j][i] != ' ')
	{
		check->player++;
		if ((j == 0) || (i == 0) || (i == check->max_i) || (j == check->max_j))
			error("Invalid player position.");
		if (i != 0 && i != check->max_i && j != 0 && j != check->max_j)
		{
			if ((map[j][i - 1] == ' ') || (map[j][i + 1] == ' ')
			|| (map[j - 1][i] == ' ') || (map[j + 1][i] == ' '))
				error("Invalid player position.");
		}
		data->map.player = map[j][i];
		map[j][i] = '0';
		data->posy = i + 0.5;
		data->posx = j + 0.5;
	}
}

static void	check_map_helper_2(t_check *check, t_data *data, int i, int j)
{
	char	**map;

	map = data->map.map_array;
	if (map[j][i] != '1' && map[j][i] != '0'
	&& map[j][i] != '\n')
	{
		if (map[j][i] == ' ')
		{
			if (i != 0 && i != check->max_i && j != 0 && j != check->max_j)
			{
				if ((map[j][i - 1] == '0') || (map[j][i + 1] == '0')
				|| (map[j - 1][i] == '0') || (map[j + 1][i] == '0'))
					error("Invalid Map.");
			}
		}
	}
}

static void	norm_helper(char **map, int j, int i)
{
	if (map[j][i - 1] == '0')
		return ;
	if ((map[j][i + 1] == '0')
	|| (map[j - 1][i] == '0') || (map[j + 1][i] == '0'))
		error("Invalid Map.");
}

static void	check_map_helper_3(t_data *data, int i, int j)
{
	char	**map;

	map = data->map.map_array;
	if (i <= data->map.len[j])
	{
		if (map[j][i] == ' ')
		{
			if (j == 0)
			{
				if ((map[j][i - 1] == '0') || (map[j][i + 1] == '0')
				|| (map[j + 1][i] == '0'))
					error("Invalid Map.");
			}
			else if (j >= (data->map.map_row - 1))
			{
				if ((map[j][i - 1] == '0') || (map[j][i + 1] == '0')
				|| (map[j - 1][i] == '0'))
					error("Invalid Map.");
			}
			else
				norm_helper(map, j, i);
		}
	}
}


void	check_map(t_data *data, t_check *check)
{
	int		i;
	int		j;
	char	**map;

	j = 0;
	map = data->map.map_array;
	check->player = 0;
	check->max_i = data->map.line_length - 1;
	check->max_j = ft_arraylen(data->map.map_array) - 1;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			
			
			i++;
		}
		j++;
	}
	if (check->player != 1)
		error("One Player position allowed.");
	check_borders(data, check);
}
*/



int recurse_map(t_data *data, int i, int j)
{
	if (i < 0 || j < 0 || i >= ft_arraylen(data->map.map_array) || ((size_t)j) >= ft_strlen(data->map.map_array[i]))
		return (0);
	if (data->map.map_array[i][j] == '1' || data->map.map_array[i][j] == '?')
		return (1);
	if (data->map.map_array[i][j] == '0')
		data->map.map_array[i][j] = '?';
	else if (data->map.map_array[i][j] == '2')
		data->map.map_array[i][j] = '?';
	else if (data->map.map_array[i][j] == 'N' || data->map.map_array[i][j] == 'S' || data->map.map_array[i][j] == 'W' || data->map.map_array[i][j] == 'E')
		data->map.map_array[i][j] = '?';
	return (recurse_map(data, i + 1, j) && recurse_map(data, i - 1, j) && recurse_map(data, i, j + 1) && recurse_map(data, i, j - 1));
}

void find_player(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i <ft_arraylen(data->map.map_array))
	{
		while(data->map.map_array[i][j])
		{
			if(data->map.map_array[i][j] == 'N' || data->map.map_array[i][j] == 'S' || data->map.map_array[i][j] == 'W' || data->map.map_array[i][j] == 'E')
			{
				data->map.player_x = j;
				data->map.player_y = i;
				data->map.player_dir = data->map.map_array[i][j];
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	fix_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < ft_arraylen(data->map.map_array))
	{
		while(data->map.map_array[i][j])
		{
			if(data->map.map_array[i][j] == '?' && i == data->map.player_y && j == data->map.player_x)
				data->map.map_array[i][j] = data->map.player_dir;
			else if(data->map.map_array[i][j] == '?')
				data->map.map_array[i][j] = '0';
			j++;
		}
		j = 0;
	    printf("%s", data->map.map_array[i]);
		i++;
	}
}

void	check_map(t_data *data, t_check *check)
{
	char	**map;

	map = data->map.map_array;
	check->player = 0;
	check->max_i = data->map.line_length - 1;
	check->max_j = ft_arraylen(data->map.map_array) - 1;
	find_player(data);
	if(recurse_map(data, data->map.player_y, data->map.player_x) == 0)
		error("Invalid Map!*");
	fix_map(data);
	data->map.player = data->map.map_array[data->map.player_y][data->map.player_x];
	map[data->map.player_y][data->map.player_x] = '0';
	data->posy = data->map.player_x + 0.5;
	data->posx = data->map.player_y + 0.5;
}
