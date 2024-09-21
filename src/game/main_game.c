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

// int worldMap[24][24] =
//     {
//         {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
//         {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
//         {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//         {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//         {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
//         {4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
//         {4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
//         {4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
//         {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
//         {4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
//         {4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
//         {4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
//         {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
//         {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
//         {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
//         {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
//         {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
//         {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
//         {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
//         {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
//         {4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
//         {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
//         {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
//         {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};


int main_loop(t_game *game)
{
    pixel_map(game, game->map.sky, game->map.floor);
    handle_raycasting(game);
    // mlx_put_image_to_window(game->mlx, game->mlx_win, game->image.img, 0, 0);
    // draw_pixel_map(game);
    // free_arr((void **)game->pixels, SCREEN_Y);

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

int handle_raycasting(t_game *game)
{
    int x = 0;

    while (x < SCREEN_X)
    {
        init_raycast_variables(game, &game->ray, x);
        looping_rays(game);
        wall_distance(game);
        wall_height(game);
        // update_map(game, &game->ray, x);
        int color = get_wall_color(game->ray.mapX, game->ray.mapY);
        color = apply_shading_if_needed(color, game->ray.side);

        drawLine(game, x, game->ray.drawStart, game->ray.drawEnd, color);
        x++;
    }
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

int end_program(void *l)
{
    (void)l;
    exit(0);
}

void init_values(t_game *game)
{
    game->map.sky.red = 135;
    game->map.sky.green = 206;
    game->map.sky.blue = 235;
    game->map.floor.red = 34;
    game->map.floor.green = 139;
    game->map.floor.blue = 34;
    game->player.playerX = 12;
    game->player.playerY = 5;
    game->player.dirX = -1;
    game->player.dirY = 0;
    game->player.planeX = 0;
    game->player.planeY = 0.66;
    game->player.moveSpeed = 0.05;
    game->player.rotSpeed = 0.05;
    game->fd = -1;
    while (++game->fd < 5)
    {
        game->texture_buffer[game->fd] = NULL;
        game->path_texture[game->fd] = NULL;
    }
    game->fd = 0;
}

int main(void)
{
    t_game *game;
    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    init_values(game);
    game->mlx = mlx_init();
    game->mlx_win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, NAME);
    game->image.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
    game->image.addr = (int *)mlx_get_data_addr(game->image.img, &game->image.bpp,
                                                &game->image.len, &game->image.endian);
    if (!load_textures(game))
        return (1);
    // t_game game;
    // t_player *player = malloc(sizeof(t_player) * 1);
    // game->player = player;
    // t_map *map = malloc(sizeof(t_map) * 1);
    // game->map = map;

    // init_texture_paths(&game);
    // if (!load_textures(&game))
    // {
    //     printf("HOLA\n");
    //     return (1);
    // }
    // load_textures(&game);
    // main_loop(game);
    mlx_loop_hook(game->mlx, &main_loop, game);
    mlx_hook(game->mlx_win, DESTROY, 0, &end_program, game);
    mlx_hook(game->mlx_win, KEY_PRESS, (1L << 0), &handle_keys, game);
    mlx_loop(game->mlx);
    return (0);
}