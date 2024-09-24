/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:49 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/24 22:36:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	player_movements(t_game *game, int direction)
{
	double	move_x;
	double	move_y;
	int		new_pos_x;
	int		new_pos_y;

	move_x = direction * game->player.moveSpeed * game->player.dirX;
	move_y = direction * game->player.moveSpeed * game->player.dirY;
	new_pos_x = (int)(game->player.playerX + move_x);
	new_pos_y = (int)(game->player.playerY + move_y);
	if (new_pos_x >= 0 && new_pos_x < SCREEN_X && new_pos_y >= 0 && \
		new_pos_y < SCREEN_Y)
	{
		if (!game->map_data.map[new_pos_x][new_pos_y])
		{
			game->player.playerX += move_x;
			game->player.playerY += move_y;
		}
	}
}

static void	player_rotations(t_game *game, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirX;
	old_plane_x = game->player.planeX;
	game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY \
		* sin(rotSpeed);
	game->player.dirY = old_dir_x * sin(rotSpeed) + game->player.dirY * \
		cos(rotSpeed);
	game->player.planeX = game->player.planeX * cos(rotSpeed) \
		- game->player.planeY * sin(rotSpeed);
	game->player.planeY = old_plane_x * sin(rotSpeed) + game->player.planeY * \
		cos(rotSpeed);
}

static void	player_vision(int keycode, t_game *game)
{
	if (keycode == A || keycode == LEFT)
		player_rotations(game, game->player.rotSpeed);
	if (keycode == D || keycode == RIGHT)
		player_rotations(game, -game->player.rotSpeed);
}

static void	player_movement(int keycode, t_game *game)
{
	if (keycode == W || keycode == UP)
		player_movements(game, FORWARD);
	if (keycode == S || keycode == DOWN)
		player_movements(game, BACKWARD);
}

int	handle_keys(int keycode, t_game *game)
{
	player_movement(keycode, game);
	player_vision(keycode, game);
	if (keycode == K_ESC)
		end_program(game);
	return (0);
}
