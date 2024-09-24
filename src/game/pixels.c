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

void initialize_tex_buff(t_game *game)
{
	int i;

	i = 0;
	game->tex_buf = ft_calloc(sizeof(int *), SCREEN_Y + 1);
	if (!game->tex_buf)
	{
		printf("NO MALLOC\n");
		exit(1);
	}
	game->tex_buf[SCREEN_Y] = NULL;
	while (i < SCREEN_Y)
	{
		game->tex_buf[i] = ft_calloc(SCREEN_X, sizeof(int));
		if (!game->tex_buf[i])
		{
			printf("NO MALLOC\n");
			exit(1);
		}
		i++;
	}
}

void draw_img(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < SCREEN_Y)
	{
		x = 0;
		while (x < SCREEN_X)
		{
			game->image.data[(y * SCREEN_X) + x] = game->tex_buf[y][x];
			x++;
		}
		y++;
	}
}

void pixel_map(t_game *game)
{
	int y;
	int x;
	int color;

	y = 0;
	while (y < SCREEN_Y)
	{
		x = 0;
		while (x < SCREEN_X)
		{
			color = game->map_data.floor_hex;
			printf("x %d\n", x);
			printf("y %d\n", y);
			game->tex_buf[y][x] = color;
			color = game->map_data.ceil_hex;
			game->tex_buf[SCREEN_Y - y - 1][x] = color;
			x++;
		}
		y++;
	}
}
