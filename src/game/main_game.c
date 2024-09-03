/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:54:42 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/07/16 12:54:42 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define mapWidth 24
#define mapHeight 24

// int calculateAndSaveToMap(t_game *info);
// void imageDraw(t_game *info);
int get_wall_color(int mapX, int mapY);
int apply_shading_if_needed(int color, int side);


int worldMap[24][24] =
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

int main_loop(t_game *game)
{
    hande_raycasting(game);
    return (1);
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

int hande_raycasting(t_game *game)
{
    int x = 0;

    while (x < SCREEN_X)
    {
        game->ray = init_raycast_variables(game, x);
        looping_rays(game);
        wall_distance(game);
        wall_height(game);

        int color = get_wall_color(game->ray->mapX, game->ray->mapY);
        color = apply_shading_if_needed(color, game->ray->side);

        drawLine(game, x, game->ray->drawStart, game->ray->drawEnd, color);
        x++;
    }
    // int x;

    // x = 0;
    // while (x < SCREEN_X)
    // {
    //     game->ray = init_raycast_variables(game, x);
    //     looping_rays(game);
    //     wall_distance(game);
    //     wall_height(game);
    //     int color;
    //     if (worldMap[game->ray->mapX][game->ray->mapY] == 1)
    //         color = 0xFF0000;
    //     else if (worldMap[game->ray->mapX][game->ray->mapY] == 2)
    //         color = 0x00FF00;
    //     else if (worldMap[game->ray->mapX][game->ray->mapY] == 3)
    //         color = 0x0000FF;
    //     else if (worldMap[game->ray->mapX][game->ray->mapY] == 4)
    //         color = 0xFFFFFF;
    //     else
    //         color = 0x123145;

    //     if (game->ray->side == 1)
    //         color = color / 2;
    //     drawLine(game, x, game->ray->drawStart, game->ray->drawEnd, color);
    //     x++;
    // }
    // TODO: REEeefactoooooooooooooooooooooor
    //    int x;

    //     x = 0;
    //     while (x < SCREEN_X)
    //     {
    //         double cameraX = (2 * x / (double)(SCREEN_X)) - 1;
    //         double rayDirectionX = game->player->dirX + game->player->planeX * cameraX;
    //         double rayDirectionY = game->player->dirY + game->player->planeY * cameraX;
    //         int mapX = (int)(game->player->playerX);
    //         int mapY = (int)(game->player->playerY);

    //         double sideDistX;
    //         double sideDistY;

    //         double deltaDistX = fabs(1 / rayDirectionX);
    //         double deltaDistY = fabs(1 / rayDirectionY);

    //         double perpWallDist;
    //         int stepX;
    //         int stepY;

    //         int hit = 0;
    //         int side;

    //         if (rayDirectionX < 0)
    //         {
    //             stepX = -1;
    //             sideDistX = (game->player->playerX - mapX) * deltaDistX;
    //         }
    //         else
    //         {
    //             stepX = 1;
    //             sideDistX = (mapX + 1.0 - game->player->playerX) * deltaDistX;
    //         }
    //         if (rayDirectionY < 0)
    //         {
    //             stepY = -1;
    //             sideDistY = (game->player->playerY - mapY) * deltaDistY;
    //         }
    //         else
    //         {
    //             stepY = 1;
    //             sideDistY = (mapY + 1.0 - game->player->playerY) * deltaDistY;
    //         }

    //         while (hit == 0)
    //         {
    //             if (sideDistX < sideDistY)
    //             {
    //                 sideDistX += deltaDistX;
    //                 mapX += stepX;
    //                 side = 0;
    //             }
    //             else
    //             {
    //                 sideDistY += deltaDistY;
    //                 mapY += stepY;
    //                 side = 1;
    //             }

    //             if (worldMap[mapX][mapY] > 0)
    //                 hit = 1;
    //         }
    //         if (side == 0)
    //             perpWallDist = (mapX - game->player->playerX + (1 - stepX) / 2) / rayDirectionX;
    //         else
    //             perpWallDist = (mapY - game->player->playerY + (1 - stepY) / 2) / rayDirectionY;

    //         int lineHeight = (int)(SCREEN_Y / perpWallDist);

    //         int drawStart = (-lineHeight / 2) + (SCREEN_Y / 2);
    //         if (drawStart < 0)
    //             drawStart = 0;
    //         int drawEnd = (lineHeight / 2) + (SCREEN_Y / 2);
    //         if (drawEnd >= SCREEN_Y)
    //             drawEnd = SCREEN_Y - 1;

    // }
    return (0);
}

int get_wall_color(int mapX, int mapY)
{
    int color;
    int tile = worldMap[mapX][mapY];

    if (tile == 1)
        color = 0xFF0000; // Rojo
    else if (tile == 2)
        color = 0x00FF00; // Verde
    else if (tile == 3)
        color = 0x0000FF; // Azul
    else if (tile == 4)
        color = 0xFFFFFF; // Blanco
    else
        color = 0x123145; // Color por defecto

    return color;
}

int apply_shading_if_needed(int color, int side)
{
    if (side == 1)
        color /= 2; // Aplica sombra
    return color;
}

void player_movements(t_game *game, int direction)
{
    double moveX = direction * game->player->moveSpeed * game->player->dirX;
    double moveY = direction * game->player->moveSpeed * game->player->dirY;

    // TODO: cambiar worldMap por game->map->map
    if (!worldMap[(int)(game->player->playerX + moveX)]
                 [(int)(game->player->playerY)])
        game->player->playerX += moveX;
    if (!worldMap[(int)game->player->playerX][(int)(game->player->playerY + moveY)])
        game->player->playerY += moveY;
}

void player_rotations(t_game *game, double rotSpeed)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = game->player->dirX;
    oldPlaneX = game->player->planeX;
    game->player->dirX = game->player->dirX * cos(rotSpeed) - game->player->dirY * sin(rotSpeed);
    game->player->dirY = oldDirX * sin(rotSpeed) * game->player->dirY * cos(rotSpeed);
    game->player->planeX = game->player->planeX * cos(rotSpeed) - game->player->planeY * sin(rotSpeed);
    game->player->planeY = oldPlaneX * sin(rotSpeed) + game->player->planeY * cos(rotSpeed);
}

// ➜  Cub3d git:(fede) ✗ gcc -o main ./src/game/main_game.c -Lminilibx-linux -lmlx -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXfixes -lm -Wall -Werror -Wextra  && ./main
void player_vision(int keycode, t_game *game)
{

    if (keycode == A || keycode == LEFT)
        player_rotations(game, game->player->rotSpeed);
    if (keycode == D || keycode == RIGHT)
        player_rotations(game, -game->player->rotSpeed);
}

void player_movement(int keycode, t_game *game)
{
    if (keycode == W || keycode == UP)
        player_movements(game, FORWARD);
    if (keycode == S || keycode == DOWN)
        player_movements(game, BACKWARD);
}
int end_program(void *l)
{
    (void)l;
    exit(0);
}

int handle_keys(int keycode, t_game *game)
{
    player_movement(keycode, game);
    player_vision(keycode, game);
    if (keycode == K_ESC)
        end_program(game);
    return (0);
}

void init_values(t_game game)
{
    game.player->playerX = 12;
    game.player->playerY = 5;
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
    game.mlx = mlx_init();
    game.mlx_win = mlx_new_window(game.mlx, SCREEN_X, SCREEN_Y, "CUB</3D");
    mlx_loop_hook(game.mlx, &main_loop, &game);
    //*Cerrar con x
    mlx_hook(game.mlx_win, DESTROY, 0, &end_program, &game);
    mlx_hook(game.mlx_win, KEY_PRESS, (1L << 0), &handle_keys, &game);
    mlx_loop(game.mlx);
}