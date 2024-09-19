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

bool pixel_map(t_game *game)
{
	int i;

	game->pixels = malloc(sizeof(int *) * SCREEN_Y + 1);
	if (!game->pixels)
		return (false);
	i = -1;
	while (++i < SCREEN_Y)
	{
		game->pixels[i] = malloc(sizeof(int) * (SCREEN_X));
		if (!game->pixels[i])
			return (free_arr((void **)game->pixels, i), false);
	}
	return (true);
}

int get_img_direction(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dirX < 0)
			return (TEXTURE_WEST);
		else
			return (TEXTURE_EAST);
	}
	else
	{
		if (ray->dirY > 0)
			return (TEXTURE_SOUTH);
		else
			return (TEXTURE_NORTH);
	}
}

void update_map(t_game *game, t_ray *ray, int x)
{
	int dir;
	int color;
	int texture;
	double pos;
	double step;

	dir = get_img_direction(ray);
	// printf("DIR: %d\n", dir);
	texture = (int)(ray->wallX * TEX_SIZE);
	if ((ray->side == 0 && ray->dirX < 0) || (ray->side == 1 && ray->dirY > 0))
		texture = TEX_SIZE - texture - 1;
	step = 1.0 * TEX_SIZE / ray->height;
	pos = (ray->drawStart - SCREEN_Y / 2 + ray->height / 2) * step;
	while (ray->drawStart < ray->drawEnd)
	{
		pos += step;
		printf("DIR %d\n", dir);
		if (game->texture_buffer[dir] == NULL)
		{
			printf("Error: Texture buffer for direction %d is not initialized\n", dir);
			return;
		}
		if (dir < 0 || dir >= 4)
		{
			printf("Error: Invalid texture direction %d\n", dir);
			return;
		}
		color = (game->texture_buffer)[dir][TEX_SIZE * ((int)pos & (TEX_SIZE - 1)) + texture];
		if (dir == TEXTURE_NORTH || dir == TEXTURE_SOUTH)
			color = (color >> 1) & 0x7F7F7F;
		if (color > 0)
			game->pixels[ray->drawStart][x] = color;
		ray->drawStart++;
	}
}

void free_arr(void **array, int n)
{
	int i;

	i = -1;
	if (n == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < n)
			if (array[i])
				free(array[i]);
	free(array);
}

void draw_pixel_map(t_game *game)
{
	t_img img;
	int x;
	int y;

	img.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	if (img.img == NULL)
		return;
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp,
										&img.len, &img.endian);
	y = -1;
	while (++y < SCREEN_Y)
	{
		x = -1;
		while (++x < SCREEN_X)
		{
			if (game->pixels[y][x] > 0)
				img.addr[y * (img.len / 4) + x] = game->pixels[y][x];
			else if (y < SCREEN_Y / 2)
			{
				printf("D: %d\n", game->map->ceiling_hex);
				img.addr[y * (img.len / 4) + x] = game->map->ceiling_hex;
			}
			else if (y < SCREEN_Y - 1)
				img.addr[y * (img.len / 4) + x] = game->map->floor_hex;
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}
