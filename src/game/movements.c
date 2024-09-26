/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:49 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/26 01:20:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
void print_map_with_player(t_game *game);
static void player_movements(t_game *game, int direction)
{
	char **map;
	double speed;
	t_player *p;

	p = &game->player;
	speed = game->player.moveSpeed;
	printf("data %d\n", (int)(game->map_data.player_y + p->dirY *
															(speed + 0.5)));
	map = game->map_data.map;
	if (direction == FORWARD)
	{
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y + p->dirY *
																	   (speed + 1))][(int)(game->map_data.player_x)]) != NULL)
		{
			printf("HOLA1\n");
			game->map_data.player_y += p->dirY * speed;
		}
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)][(int)(game->map_data.player_x + p->dirX *
																									   (speed + 1))]) != NULL)
		{
			game->map_data.player_x += p->dirX * speed;
			printf("HOLA2\n");
		}
	}
	if (direction == BACKWARD)
	{
		printf("ENTRA\n");
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y - p->dirY *
														(speed + 0.25))][(int)(game->map_data.player_x)]) != NULL)
			game->map_data.player_y -= p->dirY * speed;
		if (ft_strchr("NSEW0", map[(int)(game->map_data.player_y)][(int)(game->map_data.player_x - p->dirX *
																		 (speed + 0.25))]) != NULL)
			game->map_data.player_x -= p->dirX * speed;
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

	static void player_rotations(t_game * game, double rotSpeed)
	{
		double old_dirX;
		double old_plane_x;

		old_dirX = game->player.dirX;
		old_plane_x = game->player.planeX;
		game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
		game->player.dirY = old_dirX * sin(rotSpeed) + game->player.dirY *
														   cos(rotSpeed);
		game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
		game->player.planeY = old_plane_x * sin(rotSpeed) + game->player.planeY *
																cos(rotSpeed);
	}

	static void player_vision(int keycode, t_game *game)
	{
		if (keycode == A || keycode == LEFT)
			player_rotations(game, game->player.rotSpeed);
		if (keycode == D || keycode == RIGHT)
			player_rotations(game, -game->player.rotSpeed);
	}

	static void player_movement(int keycode, t_game *game)
	{
		if (keycode == W || keycode == UP)
			player_movements(game, FORWARD);
		if (keycode == S || keycode == DOWN)
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
