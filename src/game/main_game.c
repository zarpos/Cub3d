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

#define mapWidth 24
#define mapHeight 24

int calculateAndSaveToMap(t_info *info);
void imageDraw(t_info *info);

int worldMap[mapWidth][mapHeight] =
    {
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
        {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
        {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
        {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
        {4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
        {4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
        {4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
        {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
        {4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
        {4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
        {4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
        {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
        {4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
        {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

int main_loop(t_gam *game)
{
    calculateAndSaveToMap(info);
    imageDraw(info);
}
void drawLine(t_game *game, int x, int y1, int y2, int color)
{
    int temp;

    temp = y1;
    while (temp <= y2)
    {
        mlx_pixel_put(game->mlx, game->mlx_win, x, temp, color);
        temp++;
    }
}

int calculateAndSaveToMap(t_game *game)
{
    int x;

    x = 0;
    while (x < SCREEN_X)
    {
        double cameraX = (2 * x / (double)(SCREEN_X)) - 1;
        double rayDirectionX = game->player->dirX + game->player->planeX * cameraX;
        double rayDirectionY = game->player->dirY + game->player->planeY * cameraX;
        int mapX = (int)(game->player->player_x);
        int mapY = (int)(game->player->player_y);

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirectionX);
        double deltaDistY = fabs(1 / rayDirectionY);

        double perpWallDist;
        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirectionX < 0)
        {
            stepX = -1;
            sideDistX = (game->player->player_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player->player_x) * deltaDistX;
        }
        if (rayDirectionY < 0)
        {
            stepY = -1;
            sideDistY = (game->player->player_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player->player_y) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }
        if (side == 0)
            perpWallDist = (mapX - game->player->player_x + (1 - stepX) / 2) / rayDirectionX;
        else
            perpWallDist = (mapY - game->player->player_y + (1 - stepY) / 2) / rayDirectionY;

        int lineHeight = (int)(SCREEN_Y / perpWallDist);

        int drawStart = (-lineHeight / 2) + (SCREEN_Y / 2);
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = (lineHeight / 2) + (SCREEN_Y / 2);
        if (drawEnd >= SCREEN_Y)
            drawEnd = SCREEN_Y - 1;

        int color;
        if (worldMap[mapX][mapY] == 1)
            color = 0xFF0000;
        else if (worldMap[mapX][mapY] == 2)
            color = 0x00FF00;
        else if (worldMap[mapX][mapY] == 3)
            color = 0x0000FF;
        else if (worldMap[mapX][mapY] == 4)
            color = 0xFFFFFF;
        else
            color = 0x123145;

        if (side == 1)
            color = color / 2;
        drawLine(game, x, drawStart, drawEnd, color);
        x++;
    }
    return (0);
}

int key_press(int key, t_game *game)
{
    // WS
    if (key == W)
    {
        if (!worldMap[(int)(game->player->player_y + game->player->dirX * game->player->moveSpeed)][(int)(game->player->player_y)])
            game->player->player_x += game->player->dirX * game->player->moveSpeed;
        if (!worldMap[(int)(game->player->player_x)][(int)(game->player->player_y + game->player->dirY * game->player->moveSpeed)])
            game->player->player_y += game->player->dirY * game->player->moveSpeed;
    }

    if (key == S)
    {

        if (!worldMap[(int)(game->player->player_x - game->player->dirX * game->player->moveSpeed)][(int)(game->player->player_y)])
            game->player->player_x -= game->player->dirX * game->player->moveSpeed;
        if (!worldMap[(int)(game->player->player_x)][(int)(game->player->player_y - game->player->dirY * game->player->moveSpeed)])
            game->player->player_y -= game->player->dirY * game->player->moveSpeed;
    }

    if (key == A)
    {
        double oldDirectionX = game->player->dirX;
        game->player->dirX = game->player->dirX * cos(game->player->rotSpeed) - game->player->dirY * sin(game->player->rotSpeed);
        game->player->dirY = oldDirectionX * sin(game->player->rotSpeed) + game->player->dirY * cos(game->player->rotSpeed);
        double oldPlaneX = game->player->planeX;
        game->player->planeX = game->player->planeX * cos(game->player->rotSpeed) - game->player->planeY * sin(game->player->rotSpeed);
        game->player->planeY = oldPlaneX * sin(game->player->rotSpeed) + game->player->planeY * cos(game->player->rotSpeed);
    }

    if (key == D)
    {
        double oldDirectionX = game->player->dirX;
        game->player->dirX = game->player->dirX * cos(-game->player->rotSpeed) - game->player->dirY * sin(-game->player->rotSpeed);
        game->player->dirY = oldDirectionX * sin(-game->player->rotSpeed) + game->player->dirY * cos(-game->player->rotSpeed);
        double oldPlaneX = game->player->planeX;
        game->player->planeX = game->player->planeX * cos(-game->player->rotSpeed) - game->player->planeY * sin(-game->player->rotSpeed);
        game->player->planeY = oldPlaneX * sin(-game->player->rotSpeed) + game->player->planeY * cos(-game->player->rotSpeed);
    }
    return (0);
}

// ➜  Cub3d git:(fede) ✗ gcc -o main ./src/game/main_game.c -Lminilibx-linux -lmlx -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXfixes -lm -Wall -Werror -Wextra  && ./main
//  void player_vision(int keycode, t_game *game)
//  {
//      (void) keycode, (void) game;
//      if (keycode == A || keycode == LEFT)
//          //TODO: girar dcha
//      if (keycode == D || keycode == RIGHT)
//  }       //TODO: girar izq

// void player_movement(int keycode, t_game *game)
// {
//     (void) keycode, (void) game;
//     if (keycode == W || keycode == UP)
//         //TODO: mover parriba
//     if (keycode == S || keycode == DOWN)
// }       //TODO: pabajo
int end_program(void *l)
{
    (void)l;
    exit(0);
}

int handle_keys(int keycode, t_game *game)
{
    if (keycode == K_ESC)
        end_program(game); // TODO: Exit function
    (void)game;
    // player_movement(keycode, game);
    // player_vision(keycode, game);
    return (0);
}

void init_values(t_game game)
{
    game.player->player_x = 12;
    game.player->player_y = 5;
    game.player->dirX = -1;
    game.player->dirY = 0;
    game.player->planeX = 0;
    game.player->planeY = 0.66;
    game.player->moveSpeed = 0.05;
    game.player->rotSpeed = 0.05;
}

int main(void)
{
    t_game game;
    t_player *player = malloc(sizeof(t_player) * 1);
    game.player = player;
    init_values(game);
    printf("NUM1: %f", game.player->planeY);
    game.mlx = mlx_init();
    game.mlx_win = mlx_new_window(game.mlx, SCREEN_X, SCREEN_Y, "CUB</3D");
    mlx_loop_hook(game.mlx, &main_loop, &game);
    //*Cerrar con x
    mlx_hook(game.mlx_win, DESTROY, 0, &end_program, &game);
    mlx_hook(game.mlx_win, KEY_PRESS, (1L << 0), &key_press, &game);
    mlx_loop(game.mlx);
}