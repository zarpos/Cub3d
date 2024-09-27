/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:49 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/27 15:49:25 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_movements(t_game *game)
{
	char	**map;
	double	speed;

	speed = game->player.move_speed * 4;
	map = game->map_data.map;
	if (game->keys.w)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y + \
			game->player.dir_y * (speed + 0.5))] \
			[(int)(game->map_data.player_x)]))
			game->map_data.player_y += game->player.dir_y * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)] \
			[(int)(game->map_data.player_x + game->player.dir_x * \
				(speed + 0.5))]))
			game->map_data.player_x += game->player.dir_x * speed;
	}
	if (game->keys.s)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y - \
		game->player.dir_y * (speed + 0.5))][(int)(game->map_data.player_x)]))
			game->map_data.player_y -= game->player.dir_y * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)] \
		[(int)(game->map_data.player_x - game->player.dir_x * (speed + 0.5))]))
			game->map_data.player_x -= game->player.dir_x * speed;
	}
}

static void	lateral_mov(t_game *game)
{
	char	**map;
	double	speed;

	speed = game->player.move_speed * 4;
	map = game->map_data.map;
	if (game->keys.d)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y + \
		game->player.dir_x * (speed + 0.25))][(int)(game->map_data.player_x)]))
			game->map_data.player_y += game->player.dir_x * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)] \
		[(int)(game->map_data.player_x - game->player.dir_y * (speed + 0.25))]))
			game->map_data.player_x -= game->player.dir_y * speed;
	}
	if (game->keys.a)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y - \
		game->player.dir_x * (speed + 0.25))][(int)(game->map_data.player_x)]))
			game->map_data.player_y -= game->player.dir_x * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)] \
		[(int)(game->map_data.player_x + game->player.dir_y * (speed + 0.25))]))
			game->map_data.player_x += game->player.dir_y * speed;
	}
}

static void	player_rotations(t_game *game, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rotSpeed) - \
	game->player.dir_y * sin(rotSpeed);
	game->player.dir_y = old_dir_x * sin(rotSpeed) + \
	game->player.dir_y * cos(rotSpeed);
	game->player.plane_x = game->player.plane_x * cos(rotSpeed) - \
	game->player.plane_y * sin(rotSpeed);
	game->player.plane_y = old_plane_x * sin(rotSpeed) + \
	game->player.plane_y * cos(rotSpeed);
}

static void	player_vision(t_game *game)
{
	if (game->keys.left)
		player_rotations(game, -game->player.rot_speed);
	if (game->keys.right)
		player_rotations(game, game->player.rot_speed);
}

int	handle_movements(t_game *game)
{
	player_movements(game);
	lateral_mov(game);
	player_vision(game);
	return (0);
}
