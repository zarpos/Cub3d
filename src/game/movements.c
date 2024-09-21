/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:49 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/21 17:38:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void player_movements(t_game *game, int direction)
{
    double moveX = direction * game->player.moveSpeed * game->player.dirX;
    double moveY = direction * game->player.moveSpeed * game->player.dirY;

    int newPosX = (int)(game->player.playerX + moveX);
    int newPosY = (int)(game->player.playerY + moveY);

    if (newPosX >= 0 && newPosX < SCREEN_X && newPosY >= 0 && newPosY < SCREEN_Y)
    {
        if (!worldMap[newPosX][newPosY])
        {
            game->player.playerX += moveX;
            game->player.playerY += moveY;
        }
    }
}

static void player_rotations(t_game *game, double rotSpeed)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = game->player.dirX;
    oldPlaneX = game->player.planeX;

    game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
    game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed); // Corrección aquí
    game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
    game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
}

// ➜  Cub3d git:(fede) ✗ gcc -o main ./src/game/main_game.c -Lminilibx-linux -lmlx -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXfixes -lm -Wall -Werror -Wextra  && ./main
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
