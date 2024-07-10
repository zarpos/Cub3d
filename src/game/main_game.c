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
    mlx_loop_hook(info.mlx, &main_loop, &info);
    //*Cerrar con x
    mlx_hook(game.mlx_win, CROSS, 0, &end_program, &game);
    mlx_loop(game.mlx);


}