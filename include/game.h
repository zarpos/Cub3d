/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:52:14 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/22 21:37:27 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d.h"


typedef struct s_game
{
	void *mlx;
	void *mlx_win;
	void *img;
	int **tex_buf;
	int **texture;
	int fd;
	char *path_texture[4];
	t_map map_data;
//	t_player player;
//	t_img image;
//	t_ray ray;

} t_game;

#endif