/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:39 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/09/03 12:29:44 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void render_walls(t_game *game, t_ray *ray, int x, int y)
{
	int color;
	int aux_tex;

	aux_tex = (int)ray->tex_pos & (texHeight - 1);
	ray->tex_pos += ray->step;
	ray->tex_n = 0;
	if (ray->side == 0 && ray->dirX > 0)
		ray->tex_n = 3;
	else if (ray->side == 0 && ray->dirX < 0)
		ray->tex_n = 2;
	else if (ray->side == 1 && ray->dirX > 0)
		ray->tex_n = 1;
	// printf("ray->tex_n: %d, texHeight: %d, aux_tex: %d, ray->texX: %d\n",
	// 	   ray->tex_n, texHeight, aux_tex, ray->texX);
	color = game->texture[ray->tex_n][texHeight * aux_tex + ray->texX];
	if (ray->side == 1)
		color = (color >> 1) & 8355711;
	game->tex_buf[y][SCREEN_X - x - 1] = color;
}

void init_raycast_variables(t_game *game, t_ray *ray, int x)
{
	ray->camX = 2 * x / (double)(SCREEN_X)-1;
	ray->dirX = game->player.dirX + game->player.planeX * ray->camX;
	ray->dirY = game->player.dirY + game->player.planeY * ray->camX;
	ray->mapX = (game->map_data.player_x);
	// printf("PX %d\n", game->map_data.player_x);
	// printf("S¡MX %d\n", ray->mapX);
	ray->mapY = (game->map_data.player_y);
	if (ray->dirX == 0)			// Verificar si dirX es cero
		ray->deltaDistX = 1e30; // Asignar un valor grande para indicar distancia infinita
	else
		ray->deltaDistX = fabs(1 / ray->dirX); // Calcular deltaDistX

	if (ray->dirY == 0)			// Verificar si dirY es cero
		ray->deltaDistY = 1e30; // Asignar un valor grande para indicar distancia infinita
	else
		ray->deltaDistY = fabs(1 / ray->dirY); // Calcular deltaDistY
}

void looping_rays(t_game *game, t_ray *ray)
{
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->map_data.player_x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - game->map_data.player_x) * ray->deltaDistX;
	}

	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->map_data.player_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->map_data.player_y) * ray->deltaDistY;
	}
}

void wall_distance(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		// printf("SX %d\n", ray->stepX);
		// printf("MY %d\n", ray->mapY);
		// printf("MX %d\n", ray->mapX);
		if (game->map_data.map[ray->mapY][ray->mapX] == '1')
			break;
	}
	if (ray->side == 0)
		ray->wallDist = (ray->mapX - game->map_data.player_x +
						 (1 - ray->stepX) / 2) /
						ray->dirX;
	else
		ray->wallDist = (ray->mapY - game->map_data.player_y + (1 - ray->stepY) / 2) / ray->dirY;
}

void wall_height(t_game *game, t_ray *ray)
{
	// printf("WD: %f\n", ray->wallDist);
	// printf("DIRX: %f\n", ray->dirX);
	// printf("DIRY: %f\n", ray->dirY);
	// printf("DAT %f\n", game->map_data.player_x + ray->wallDist * ray->dirX);
	// printf("DAT2 %f\n", game->map_data.player_x + ray->wallDist * ray->dirY);
	ray->lh = (int)(SCREEN_Y / ray->wallDist);
	ray->drawStart = -(ray->lh / 2) + (SCREEN_Y / 2);
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = (ray->lh / 2) + (SCREEN_Y / 2);
	if (ray->drawEnd >= SCREEN_Y)
		ray->drawEnd = SCREEN_Y - 1;
	if (ray->side == 0)
		ray->wallX = game->map_data.player_x + ray->wallDist * ray->dirX;
	else
		ray->wallX = game->map_data.player_x + ray->wallDist * ray->dirY;
	ray->wallX -= floor(ray->wallX);
	ray->texX = (int)(ray->wallX * (double)texWidth);
	// printf("WALLX %f\n", ray->wallX);
	if (ray->side == 0 && ray->dirX > 0)
		ray->texX = texWidth - ray->texX - 1;
	if (ray->side == 1 && ray->dirY < 0)
		ray->texX = texWidth - ray->texX - 1;
	ray->step = 1.0 * texHeight / ray->lh;
	ray->tex_pos = (ray->drawStart - SCREEN_Y / 2 + ray->lh / 2) * ray->step;
	// printf("TEX %d\n", ray->texX);
}
