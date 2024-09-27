/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:49 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/27 13:31:14 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
void print_map_with_player(t_game *game);

void player_movements(t_game *game)
{
	char	**map;
	double	speed;

	speed = game->player.moveSpeed * 4;
	map = game->map_data.map;

	if (game->keys.w)
	{
		// Movimiento hacia adelante
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y + game->player.dirY * (speed + 0.5))][(int)(game->map_data.player_x)]) != NULL)
			game->map_data.player_y += game->player.dirY * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)][(int)(game->map_data.player_x + game->player.dirX * (speed + 0.5))]) != NULL)
			game->map_data.player_x += game->player.dirX * speed;
	}
	if (game->keys.s)
	{
		// Movimiento hacia atrás
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y - game->player.dirY * (speed + 0.5))][(int)(game->map_data.player_x)]) != NULL)
			game->map_data.player_y -= game->player.dirY * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)][(int)(game->map_data.player_x - game->player.dirX * (speed + 0.5))]) != NULL)
			game->map_data.player_x -= game->player.dirX * speed;
	}
}


static void lateral_mov(t_game *game)
{
char	**map;
	double	speed;

	speed = game->player.moveSpeed * 4;
	map = game->map_data.map;
	if (game->keys.d)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y + game->player.dirX * \
		(speed + 0.25))][(int)(game->map_data.player_x)]) != NULL)
			game->map_data.player_y += game->player.dirX * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)][(int)(game->map_data.player_x - game->player.dirY * \
		(speed + 0.25))]) != NULL)
			game->map_data.player_x -= game->player.dirY * speed;
	}
	if (game->keys.a)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y - game->player.dirX * \
		(speed + 0.25))][(int)(game->map_data.player_x)]) != NULL)
			game->map_data.player_y -= game->player.dirX * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)][(int)(game->map_data.player_x + game->player.dirY * \
		(speed + 0.25))]) != NULL)
			game->map_data.player_x += game->player.dirY * speed;
	}
}
// void print_map_with_player(t_game * game)
// {
// 	char **map = game->map_data.map;
// 	int map_height = game->map_data.max_y; // Ajusta esto si tienes una variable de altura del mapa
// 	int map_width = game->map_data.max_x;  // Ajusta esto si tienes una variable de ancho del mapa
// 	int player_x = (int)game->map_data.player_y;
// 	int player_y = (int)game->map_data.player_y;

// 	for (int y = 0; y < map_height; y++)
// 	{
// 		for (int x = 0; x < map_width; x++)
// 		{
// 			if (y == player_y && x == player_x)
// 				printf("P "); // Marca la posición del jugador con una "P"
// 			else
// 				printf("%c ", map[y][x]);
// 		}
// 		printf("\n");
// 	}
// }

static void player_rotations(t_game *game, double rotSpeed)
{
	double old_dirX;
	double old_plane_x;

	old_dirX = game->player.dirX;
	old_plane_x = game->player.planeX;
	game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
	game->player.dirY = old_dirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
	game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
	game->player.planeY = old_plane_x * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
}

static void player_vision(t_game *game)
{
	if (game->keys.left)
		player_rotations(game, -game->player.rotSpeed);
	if (game->keys.right)
		player_rotations(game, game->player.rotSpeed);
}

// static void player_movement(t_game *game)
// {
// 	player_movements(game);
// 	// if (game->keys.a)
// 	// 	lateral_mov(game, A);
// 	// if (game->keys.d)
// 	// 	lateral_mov(game, D);
// }

int handle_movements(t_game *game)
{
	player_movements(game);
	lateral_mov(game);
	player_vision(game);
	return (0);
}
