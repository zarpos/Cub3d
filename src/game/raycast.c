/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:33:39 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/07/16 17:16:08 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_raycast_variables(t_game *game, int x)
{
	t_ray *ray;

	ray = game->ray;
	ray->camX = (2 * x / (double)(SCREEN_X)) - 1;
	ray->rayDirX = game->player->dirX + game->player->planeX * ray->camX;
	ray->rayDirY = game->player->dirY + game->player->planeY * ray->camX;
	ray->mapX = (int)(game->player->playerX);
	ray->mapY = (int)(game->player->playerY);
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
}

void	looping_rays(t_game *game)
{
	t_ray *ray;

	ray = game->ray;
	if ()
	{
		
	}
}