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

int	main_loop(t_game *game)
{
	pixel_map(game);
	handle_raycasting(game);
	draw_img(game);
	mlx_do_sync(game->mlx);
	return (1);
}

int	handle_raycasting(t_game *game)
{
	int		x;
	int		y;
	t_ray	ray;

	x = 0;
	y = 0;
	while (x < SCREEN_X)
	{
		init_raycast_variables(game, &ray, x);
		looping_rays(game, &ray);
		wall_distance(game, &ray);
		wall_height(game, &ray);
		y = game->ray.drawStart;
		while (y < game->ray.drawEnd)
		{
			render_walls(game, game->ray, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

int	end_program(void *l)
{
	(void)l;
	exit(0);
}

void	init_values(t_game *game)
{
	game->map.sky.red = 135;
	game->map.sky.green = 206;
	game->map.sky.blue = 235;
	game->map.floor.red = 34;
	game->map.floor.green = 139;
	game->map.floor.blue = 34;
	game->player.playerX = 12;
	game->player.playerY = 5;
	game->player.dirX = -1;
	game->player.dirY = 0;
	game->player.planeX = 0;
	game->player.planeY = 0.66;
	game->player.moveSpeed = 0.05;
	game->player.rotSpeed = 0.05;
}

int	main(void)
{
	t_game		*game;
	t_parser	*parser;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	init_values(game);
	load_imgs(game, parser);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, NAME);
	game->image.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	game->image.data = (int *)mlx_get_data_addr(game->image.img, \
		&game->image.bpp, &game->image.len, &game->image.endian);
	mlx_loop_hook(game->mlx, &main_loop, game);
	mlx_hook(game->mlx_win, DESTROY, 0, &end_program, game);
	mlx_hook(game->mlx_win, KEY_PRESS, (1L << 0), &handle_keys, game);
	mlx_loop(game->mlx);
	return (0);
}
