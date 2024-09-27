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

void	render_walls(t_game *game, t_ray *ray, int x, int y)
{
	int	color;
	int	tex_y;

	tex_y = (int)ray->tex_pos & (TEXHEIGHT - 1);
	ray->tex_pos += ray->step;
	ray->tex_n = 0;
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_n = 3;
	else if (ray->side == 0 && ray->dir_x < 0)
		ray->tex_n = 2;
	else if (ray->side == 1 && ray->dir_y > 0)
		ray->tex_n = 1;
	color = game->texture[ray->tex_n][TEXHEIGHT * tex_y + ray->tex_x];
	if (ray->side == 1)
		color = (color >> 1) & 8355711;
	game->tex_buf[y][SCREEN_X - x - 1] = color;
}

void	init_raycast_variables(t_game *game, t_ray *ray, int x)
{
	ray->cam_x = 2 * x / (double)SCREEN_X - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->cam_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->cam_x;
	ray->map_x = (int)game->map_data.player_x;
	ray->map_y = (int)game->map_data.player_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	looping_rays(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (game->map_data.player_x - ray->map_x) * \
		ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - game->map_data.player_x) * \
		ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (game->map_data.player_y - ray->map_y) * \
		ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - game->map_data.player_y) * \
		ray->deltadist_y;
	}
}

void	wall_distance(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ft_strchr("NSEW0", game->map_data.map[ray->map_y] \
		[ray->map_x]) == NULL)
			ray->hit = 1;
	}
}

void	wall_height(t_game *game, t_ray *ray)
{
	ray->wall_dist = (ray->map_y - game->map_data.player_y + \
	(1 - ray->step_y) / 2) / ray->dir_y;
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - game->map_data.player_x + \
		(1 - ray->step_x) / 2) / ray->dir_x;
	ray->lh = (int)(SCREEN_Y / ray->wall_dist);
	ray->draw_start = -ray->lh / 2 + SCREEN_Y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->lh / 2 + SCREEN_Y / 2;
	if (ray->draw_end >= SCREEN_Y)
		ray->draw_end = SCREEN_Y - 1;
	ray->wall_x = game->map_data.player_x + ray->wall_dist * ray->dir_x;
	if (ray->side == 0)
		ray->wall_x = game->map_data.player_y + ray->wall_dist * ray->dir_y;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEXWIDTH);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = TEXWIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = TEXWIDTH - ray->tex_x - 1;
	ray->step = 1.0 * TEXHEIGHT / ray->lh;
	ray->tex_pos = (ray->draw_start - SCREEN_Y / 2 + ray->lh / 2) * ray->step;
}
