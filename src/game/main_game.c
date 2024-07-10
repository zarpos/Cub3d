/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:12:56 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/07/10 17:02:46 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//gcc -o main ./src/game/main_game.c -Lminilibx-linux -lmlx -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXfixes -lm -Wall -Werror -Wextra  && ./main
/*
*NOTAS:
	*Algoritmo basado en DDA(Análisis diferencial digital)
	*Pos jugador: (coordenada x e y)
	*Un solo vector, al ser 2D
	*Plano de la cámara(representa la superficie de la pantalla) debe ser perpendicular a la pantalla y apuntar dentro de ella
	*Pos jugador es 1 punto frente al plano de la cámara
*/


int	game_loop(void *ml)
{
	t_game *game;

	printf("Hola\n");
	game = ml; // cast to the mlx structure
	game->mlx_win = mlx_new_window(game->mlx, 1920, 1080, "Hello world!");
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	// // hook(game, 0, 0);
	// // cast_rays(mlx);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0); // put the image to the window	
	return (1);
}
void start_game(t_map *map)
{
	t_game	game;

	game.map = map;
	game.player = calloc(1, sizeof(t_player));	 
	game.mlx = mlx_init(SCREEN_X, SCREEN_Y, "Cub3D", 0);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	// game.mlx = mlx_init();
	// game.mlx_win = mlx_new_window(game.mlx, 1920, 1080, "Hello world!");
	mlx_loop(game.mlx);
}

t_map	*init_data(void)
{
	t_map *map = calloc(1, sizeof(t_map));
	map->map = calloc(10, sizeof(char *));
	map->map[0] = strdup("1111111111111111111111111");
	map->map[1] = strdup("1000000000000000000100001");
	map->map[2] = strdup("1001000000000P00000000001");
	map->map[3] = strdup("1001000000000000001000001");
	map->map[4] = strdup("1001000000000000001000001");
	map->map[5] = strdup("1001000000100000001000001");
	map->map[6] = strdup("1001000000000000001000001");
	map->map[7] = strdup("1001000000001000001000001");
	map->map[8] = strdup("1111111111111111111111111");
	map->map[9] = NULL;
	map->player_y = 3; 
	map->player_x = 14;
	map->map_width = 25;
	map->map_height = 9;
	return (map);
}

int main(void)
{
	t_map	*map;
	map = init_data();
	start_game(map);
	return (0);
}