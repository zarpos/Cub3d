/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:17:17 by marvin            #+#    #+#             */
/*   Updated: 2024/07/10 23:17:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
//➜  Cub3d git:(fede) ✗ gcc -o main ./src/game/main_game.c -Lminilibx-linux -lmlx -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXfixes -lm -Wall -Werror -Wextra  && ./main
void player_vision(int keycode, t_game *game)
{
    (void) keycode, (void) game;
    if (keycode == A || keycode == LEFT)
        //TODO: mover dcha
    if (keycode == D || keycode == RIGHT)
}       //TODO: izq 

void player_movement(int keycode, t_game *game)
{
    (void) keycode, (void) game;
    if (keycode == W || keycode == UP)
        //TODO: mover parriba
    if (keycode == S || keycode == DOWN)
}       //TODO: pabajo

int handle_keys(int keycode, t_game *game)
{
    (void) game;
    if (keycode == K_ESC)
        exit (0);//TODO: Exit function
    player_movement(keycode, game);
    player_vision(keycode, game);
    return (0);
}


int main_loop(void *game)
{
    t_game *g;

    g = game;
    (void) game, (void)g;   // g->player->dirX = 0;
    // printf("%f", g->player->dirX);
    return (0);

}
int end_program(void *l)
{
	(void) l;
	exit(0);
}



int main (void)
{
    t_game game;
    game.mlx = mlx_init();
    // mlx_loop_hook(info.mlx, &main_loop, &info);
    game.mlx_win = mlx_new_window(game.mlx, SCREEN_X, SCREEN_Y, "CUB</3D");
    //*Cerrar con x
    mlx_hook(game.mlx_win, DESTROY, 0, &end_program, &game);
    mlx_hook(game.mlx, KEY_PRESS, 1L<<0, &handle_keys, &game);
    mlx_loop(game.mlx);


}