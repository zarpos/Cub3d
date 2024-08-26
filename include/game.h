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
#define SCREEN_X 640
#define SCREEN_Y 480
#define KEY_PRESS 2
#define W 119
#define A 97
#define S 115
#define D 100

#define K_ESC 65307
#define DESTROY 17

#define UP 65362
#define DOWN 65364
#define RIGHT 65363
#define LEFT 65361

#define texWidth 64
#define texHeight 64

#define FORWARD 1
#define BACKWARD -1


#define TEXTURE_NORTH 0
#define TEXTURE_SOUTH 1
#define TEXTURE_WEST 2
#define TEXTURE_EAST 3

typedef struct s_player
{
	double	playerX;
	double	playerY;
	double	dirX;
	double	dirY;
	double	moveSpeed;
	double	rotSpeed;
	double	planeX;
    double	planeY;
} t_player;

typedef struct s_ray
{
	double	camX;
	double	dirX;
	double	dirY;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	wallDist;
	int		side;
	int		hit;
	int		lh;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	
}			t_ray;
typedef struct s_im
{
	void	*img;
	char	*addr;
	int		endian;
	int		len;
	int		bpp;
}				t_im;

typedef struct s_map
{	
	int		**map;
	size_t	map_width;
	size_t	map_height;
	int     **buf;
    int     texture[8][texHeight * texWidth];

} t_map;

typedef	struct s_game
{
	void 		*mlx;
	void 		*mlx_win;
	void		*img;
	t_map		*map;
	t_player	*player;
	t_im		*image;
	t_ray		*ray;	    
	
}		t_game;

int 	hande_raycasting(t_game *game);
t_ray	*init_raycast_variables(t_game *game, int x);
void	looping_rays(t_game *game);
void	wall_distance(t_game *game);
void	wall_height(t_game *game);

extern int worldMap[24][24];

#endif