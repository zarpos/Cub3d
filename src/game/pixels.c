/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:00:18 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/18 18:05:36 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void print_pixel(t_img img, int x, int y, int color)
{
    if (x >= 0 && y >= 0 && x < img.width && y < img.height && img.data != NULL)
    {
        int bytes_per_pixel = img.bpp >> 3;
        int index = (y * img.width + x) * bytes_per_pixel;

        // Depuración: imprime valores clave
        // printf("x: %d, y: %d, index: %d, color: %d, width: %d, height: %d, bpp: %d\n", 
        //        x, y, index, color, img.width, img.height, img.bpp);
        
        // Chequeo de límites modificado
        if (index >= 0 && index < (img.width * img.height * bytes_per_pixel)) 
            *(unsigned int *)(img.data + index) = color;
    }
}





int to_rgba(int r, int g, int b, int alpha)
{
	if (alpha > 255 || r > 255 || g > 255 || b > 255)
		return (0);
	return (alpha << 24 | r << 16 | g << 8 | b);
}

void pixel_map(t_game *game, t_colors sky, t_colors floor)
{
    int y = 0;
    while (y < SCREEN_Y)  // Asegúrate de que no excedas SCREEN_Y
    {
        int x = 0;
        while (x < SCREEN_X)  // Asegúrate de que no excedas SCREEN_X
        {
            if (y < SCREEN_Y / 2)
                print_pixel(game->image, x, y, to_rgba(sky.red, sky.green, sky.blue, 0));
            else
                print_pixel(game->image, x, y, to_rgba(floor.red, floor.green, floor.blue, 0));
            x++;
        }
        y++;
    }
}


// int get_img_direction(t_ray *ray)
// {
// 	if (ray->side == 0)
// 	{
// 		if (ray->dirX < 0)
// 			return (TEXTURE_WEST);
// 		else
// 			return (TEXTURE_EAST);
// 	}
// 	else
// 	{
// 		if (ray->dirY > 0)
// 			return (TEXTURE_SOUTH);
// 		else
// 			return (TEXTURE_NORTH);
// 	}
// }

// void update_map(t_game *game, t_ray *ray, int x)
// {
// 	int dir;
// 	int color;
// 	int texture;
// 	double pos;
// 	double step;

// 	dir = get_img_direction(ray);
// 	texture = (int)(ray->wallX * TEX_SIZE);
// 	if ((ray->side == 0 && ray->dirX < 0) || (ray->side == 1 && ray->dirY > 0))
// 		texture = TEX_SIZE - texture - 1;
// 	step = 1.0 * TEX_SIZE / ray->height;
// 	pos = (ray->drawStart - SCREEN_Y / 2 + ray->height / 2) * step;
// 	while (ray->drawStart < ray->drawEnd)
// 	{
// 		pos += step;
// 		if (game->texture_buffer[dir] == NULL)
// 		{
// 			printf("Error: Texture buffer for direction %d is not initialized\n", dir);
// 			return;
// 		}
// 		if (dir < 0 || dir >= 4)
// 		{
// 			printf("Error: Invalid texture direction %d\n", dir);
// 			return;
// 		}
// 		color = (game->texture_buffer)[dir][TEX_SIZE * ((int)pos & (TEX_SIZE - 1)) + texture];
// 		if (dir == TEXTURE_NORTH || dir == TEXTURE_SOUTH)
// 			color = (color >> 1) & 0x7F7F7F;
// 		if (color > 0)
// 			game->pixels[ray->drawStart][x] = color;
// 		ray->drawStart++;
// 	}
// }

// void free_arr(void **array, int n)
// {
// 	int i;

// 	i = -1;
// 	if (n == -1)
// 		while (array[++i])
// 			free(array[i]);
// 	else
// 		while (++i < n)
// 			if (array[i])
// 				free(array[i]);
// 	free(array);
// }

// void draw_pixel_map(t_game *game)
// {
// 	t_img img;
// 	int x;
// 	int y;

// 	img.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
// 	if (img.img == NULL)
// 		return;
// 	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp,
// 										&img.len, &img.endian);
// 	y = -1;
// 	while (++y < SCREEN_Y)
// 	{
// 		x = -1;
// 		while (++x < SCREEN_X)
// 		{
// 			if (game->pixels[y][x] > 0)
// 				img.addr[y * (img.len / 4) + x] = game->pixels[y][x];
// 			else if (y < SCREEN_Y / 2)
// 			{
// 				printf("D: %d\n", game->map.ceiling_hex);
// 				img.addr[y * (img.len / 4) + x] = game->map.ceiling_hex;
// 			}
// 			else if (y < SCREEN_Y - 1)
// 				img.addr[y * (img.len / 4) + x] = game->map.floor_hex;
// 		}
// 	}
// 	mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
// 	mlx_destroy_image(game->mlx, img.img);
// }
