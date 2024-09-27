/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:23:42 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/27 13:34:16 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_chars(t_game *game, char value, int x, int y)
{
	if (value != '1' && value != '0' && value != 'N'
			&& value != 'S' && value != 'E' && value != 'W' && value != ' ')
		ft_error("Ivalid char detected");

	if (value == 'N' || value == 'S' || value == 'E' || value == 'W')
	{
		game->map_data.player_y = (y * WALL_SIZE) + (WALL_SIZE / 2);
		game->map_data.player_x = (x * WALL_SIZE) + (WALL_SIZE / 2);
		return (1);
	}
	return (0);
}

void check_map_chars(t_game *game, char **map)
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
			player_flag += check_chars(game, map[y][x], x, y);
	}
	if (player_flag > 1)
		ft_error("Multiple players found");
	if (!player_flag)
		ft_error("No player position found");
}

void parsing(int argc, char **argv, t_game *game)
{
	char **file_content;
	char **map;

	file_content = check_args(argc, argv);
	set_texture(game, file_content);
	map = file_content + 6;
	check_map_chars(game, map);
	check_closed_walls(map);
	game->map_data.map = map;
}
