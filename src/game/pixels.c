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

#include "game.h"

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

void	update_map()
{
	
}