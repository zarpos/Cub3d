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
				game->map_data.player_x = x + 0.5;
				game->map_data.player_y = y + 0.5;
				game->player.dirX = 0;
				game->player.dirY = -1;
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
	y = 0;
	while (x < SCREEN_X)
	{
		init_raycast_variables(game, &ray, x);
		looping_rays(game, &ray);
		wall_distance(game, &ray);
		wall_height(game, &ray);
		y = game->ray.drawStart;
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
	// game->player.dirX = -1;
	// game->player.dirY = 0;
	// game->player.planeX = 0;
	// game->player.planeY = 0.66;
	game->player.moveSpeed = 0.05;
	game->player.rotSpeed = 0.05;
	get_player_pos(game);
}

/* int	main(void)
{
	t_game		game;
	t_parser	parser;

	// game = malloc(sizeof(t_game));
	// if (!game)
	// 	return (1);
	init_values(&game);
	initialize_tex_buff(&game);
	parser.rp = 7;
	parser.err = 0;
	parser.floor_col[0] = 220;
	parser.floor_col[1] = 225;
	parser.floor_col[2] = 225;
	parser.ceil_col[0] = 255;
	parser.ceil_col[1] = 255;
	parser.ceil_col[2] = 200;
	parser.no = MOSSY;
	parser.ea = BRICK;
	parser.we = PURPLE;
	parser.so = WOOD;
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, SCREEN_X, SCREEN_Y, NAME);
	load_imgs(&game, &parser);
	game.image.img = mlx_new_image(game.mlx, SCREEN_X, SCREEN_Y);
	game.image.data = (int *)mlx_get_data_addr(game.image.img, \
		&game.image.bpp, &game.image.len, &game.image.endian);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.mlx_win, DESTROY, 0, &end_program, &game);
	mlx_hook(game.mlx_win, KEY_PRESS, (1L << 0), &handle_keys, &game);
	mlx_loop(game.mlx);
	return (0);
} */
