/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:23:42 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/21 22:34:45 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int check_chars(t_map *map_data, char value, int x, int y)
{
	if (value != '1' && value != '0' && value != 'N' && value != 'S' && value != 'E' && value != 'W' && value != ' ')
		ft_error("Invalid value found in map");

	if (value == 'N' || value == 'S' || value == 'E' || value == 'W')
	{
		map_data->player_y = (y * WALL_SIZE) + (WALL_SIZE / 2);
		map_data->player_x = (x * WALL_SIZE) + (WALL_SIZE / 2);
		return (1);
	}
	return (0);
}

static void check_map_chars(t_map *map_data, char **map)
{
	int x;
	int y;
	int player_flag;

	y = -1;
	player_flag = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			player_flag += check_chars(map_data, map[y][x], x, y);
	}
	if (player_flag > 1)
		ft_error("Multiple players found");
	if (!player_flag)
		ft_error("No player position found");
}

void parsing(char **argv, t_map *map_data)
{
	char **file_content;
	char **map;

	file_content = read_file(argv);
	get_values(map_data, file_content);
	map = file_content + 6;
	check_map_chars(map_data, map);
	check_closed_walls(map);
	map_data->map = map;
}