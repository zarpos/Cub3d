/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:52:14 by drubio-m          #+#    #+#             */
/*   Updated: 2024/07/10 15:43:44 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "cub3d.h"

#define MOSSY "../src/sprites/mossy.png"
#define PURPLE "../src/sprites/purplestone.png"
#define BRICK "../src/sprites/redbrick.png"
#define WOOD "../src/sprites/wood.png"
#define SCREEN_X 1920
#define SCREEN_Y 1080

typedef struct s_player
{
	int player_x;
	int player_y;
} t_player;



typedef struct s_map
{	
	char	**map;
	size_t	map_width;
	size_t	map_height;
	int		player_x;
	int		player_y;
} t_map;

typedef	struct s_game
{
	void 		*mlx;
	void 		*mlx_win;
	void		*img;
	t_map		*map;
	t_player	*player;
	
}	t_game;


#endif