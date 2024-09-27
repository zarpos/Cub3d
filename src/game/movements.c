/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:49 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/27 15:37:04 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_movements(t_game *game)
{
	char	**map;
	double	speed;

	speed = game->player.moveSpeed * 4;
	map = game->map_data.map;
	if (game->keys.w)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y + \
			game->player.dirY * (speed + 0.5))] \
			[(int)(game->map_data.player_x)]))
			game->map_data.player_y += game->player.dirY * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)] \
			[(int)(game->map_data.player_x + game->player.dirX * \
				(speed + 0.5))]))
			game->map_data.player_x += game->player.dirX * speed;
	}
	if (game->keys.s)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y - \
		game->player.dirY * (speed + 0.5))][(int)(game->map_data.player_x)]))
			game->map_data.player_y -= game->player.dirY * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)] \
		[(int)(game->map_data.player_x - game->player.dirX * (speed + 0.5))]))
			game->map_data.player_x -= game->player.dirX * speed;
	}
}

static void	lateral_mov(t_game *game)
{
	char	**map;
	double	speed;

	speed = game->player.moveSpeed * 4;
	map = game->map_data.map;
	if (game->keys.d)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y + \
		game->player.dirX * (speed + 0.25))][(int)(game->map_data.player_x)]))
			game->map_data.player_y += game->player.dirX * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)] \
		[(int)(game->map_data.player_x - game->player.dirY * (speed + 0.25))]))
			game->map_data.player_x -= game->player.dirY * speed;
	}
	if (game->keys.a)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y - \
		game->player.dirX * (speed + 0.25))][(int)(game->map_data.player_x)]))
			game->map_data.player_y -= game->player.dirX * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)] \
		[(int)(game->map_data.player_x + game->player.dirY * (speed + 0.25))]))
			game->map_data.player_x += game->player.dirY * speed;
	}
}

static void	player_rotations(t_game *game, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirX;
	old_plane_x = game->player.planeX;
	game->player.dirX = game->player.dirX * cos(rotSpeed) - \
	game->player.dirY * sin(rotSpeed);
	game->player.dirY = old_dir_x * sin(rotSpeed) + \
	game->player.dirY * cos(rotSpeed);
	game->player.planeX = game->player.planeX * cos(rotSpeed) - \
	game->player.planeY * sin(rotSpeed);
	game->player.planeY = old_plane_x * sin(rotSpeed) + \
	game->player.planeY * cos(rotSpeed);
}

static void	player_vision(t_game *game)
{
	if (game->keys.left)
		player_rotations(game, -game->player.rotSpeed);
	if (game->keys.right)
		player_rotations(game, game->player.rotSpeed);
}

int	handle_movements(t_game *game)
{
	player_movements(game);
	lateral_mov(game);
	player_vision(game);
	return (0);
}
