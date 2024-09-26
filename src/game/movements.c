/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:49 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/27 01:03:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
void print_map_with_player(t_game *game);

//TODO: cambiar y hacer una structura para las teclas
void player_movements(t_game *game, int direction)
{
	double pos_x;
	double pos_y;
	t_player *player;

	player = &game->player;

	pos_x = game->map_data.player_x + direction * player->dirX * game->player.moveSpeed;
	pos_y = game->map_data.player_y + direction * player->dirY * game->player.moveSpeed;

	printf("DIR_X: %f\n", player->dirX);
	if (game->map_data.map[(int)game->map_data.player_y]
						  [(int)(pos_x + direction * player->dirX * 1)] != '1')
		game->map_data.player_x = pos_x;
	printf("pos_x: %f\n", pos_x);
	if (game->map_data.map[(int)(pos_y + direction * player->dirY * 1)]
						  [(int)game->map_data.player_x] != '1')
		game->map_data.player_y = pos_y;
	printf("pos_y: %f\n", pos_y);
}

static void lateral_mov(t_game *game, int key)
{
	double pos_x;
	double pos_y;
	t_player *player;

	player = &game->player;
	if (key == D)
	{
		pos_x = game->map_data.player_x + player->planeX * game->player.moveSpeed;
		pos_y = game->map_data.player_y + player->planeY * game->player.moveSpeed;
		if (game->map_data.map[(int)game->map_data.player_y]
							  [(int)(pos_x + player->planeX * 1)] == '0')
			game->map_data.player_x = pos_x;
		if (game->map_data.map[(int)(pos_y + player->planeY * 1)]
							  [(int)game->map_data.player_x] == '0')
			game->map_data.player_y = pos_y;
	}
	else if (key == A)
	{
		pos_x = game->map_data.player_x - player->planeX * game->player.moveSpeed;
		pos_y = game->map_data.player_y - player->planeY * game->player.moveSpeed;
		if (game->map_data.map[(int)game->map_data.player_y]
							  [(int)(pos_x - player->planeX * 1)] == '0')
			game->map_data.player_x = pos_x;
		if (game->map_data.map[(int)(pos_y - player->planeY * 1)]
							  [(int)game->map_data.player_x] == '0')
			game->map_data.player_y = pos_y;
	}
}
// void print_map_with_player(t_game * game)
// {
// 	char **map = game->map_data.map;
// 	int map_height = game->map_data.max_y; // Ajusta esto si tienes una variable de altura del mapa
// 	int map_width = game->map_data.max_x;  // Ajusta esto si tienes una variable de ancho del mapa
// 	int player_x = (int)game->map_data.player_x;
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

static void player_vision(int keycode, t_game *game)
{
	if (keycode == LEFT)
		player_rotations(game, -game->player.rotSpeed);
	if (keycode == RIGHT)
		player_rotations(game, game->player.rotSpeed);
	if (keycode == A)
		lateral_mov(game, A);
	if (keycode == D)
		lateral_mov(game, D);
}

static void player_movement(int keycode, t_game *game)
{
	if (keycode == W)
		player_movements(game, FORWARD);
	if (keycode == S)
		player_movements(game, BACKWARD);
}

int handle_keys(int keycode, t_game *game)
{
	player_movement(keycode, game);
	player_vision(keycode, game);
	if (keycode == K_ESC)
		end_program(game);
	return (0);
}
