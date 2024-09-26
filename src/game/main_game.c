/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:54:42 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/07/16 12:54:42 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_orientation(t_game *game, char **map, int i, int j)
{
	char c;

	c = map[j][i];
	if (c == 'S')
	{
		game->player.dirX = 0;
		game->player.dirY = 1;
	}
	else if (c == 'E')
	{
		game->player.dirX = 1;
		game->player.dirY = 0;
	}
	else if (c == 'W')
	{
		game->player.dirX = -1;
		game->player.dirY = 0;
	}
	else if (c == 'N')
	{
		game->player.dirX = 0;
		game->player.dirY = -1;
	}
	game->player.planeX = game->player.dirY * 0.66;
	game->player.planeY = -game->player.dirX * 0.66;
}

static void get_player_pos(t_game *game)
{
	char **map;
	int y;
	int x;

	y = 0;
	map = game->map_data.map;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\n' && map[y][x])
		{
			if (ft_strchr("NESW", map[y][x]))
			{
				game->map_data.player_x = x;
				game->map_data.player_y = y;
				// game->player.dirX = 0;
				// game->player.dirY = 0;
				init_orientation(game, map, x, y);
			}
			x++;
		}
		y++;
	}
}

int main_loop(t_game *game)
{
	pixel_map(game);
	handle_raycasting(game);
	draw_img(game);
	mlx_do_sync(game->mlx);
	return (1);
}

int handle_raycasting(t_game *game)
{
	int x;
	int y;
	t_ray ray;

	x = 0;
	while (x < SCREEN_X)
	{
		init_raycast_variables(game, &ray, x);
		looping_rays(game, &ray);
		wall_distance(game, &ray);
		wall_height(game, &ray);
		y = ray.drawStart;
		while (y < ray.drawEnd)
		{
			render_walls(game, &ray, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

int end_program(void *l)
{
	(void)l;
	exit(0);
}

void init_values(t_game *game)
{

	game->player.moveSpeed = 0.05;
	game->player.rotSpeed = 0.05;
	game->tex_buf = NULL;
	game->texture = NULL;
	get_player_pos(game);
}
