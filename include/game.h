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

#define MOSSY "./src/sprites/mossy.xpm"
#define PURPLE "./src/sprites/purplestone.xpm"
#define BRICK "./src/sprites/redbrick.xpm"
#define WOOD "./src/sprites/wood.xpm"
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

#define TEX_SIZE 64

#define FLOOR_PATH "../sprites/mossy.xpm"
#define WALL_PATH "./sprites/wood.xpm"

#define NAME "CUB</3D"

typedef struct s_player
{
	double playerX;
	double playerY;
	double dirX;
	double dirY;
	double moveSpeed;
	double rotSpeed;
	double planeX;
	double planeY;
} t_player;

typedef struct s_parser
{
	int	rp;
	int err;
	char *no;
	char *so;
	char *we;
	char *ea;
	int floor_col[3];
	int ceil_col[3];

} t_parser;


typedef struct s_ray
{
	double camX;
	double dirX;
	double dirY;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double wallDist;
	int side;
	int hit;
	int height;
	int lh;
	int drawStart;
	int drawEnd;
	double wallX;
	int texX;
	double step;
	double tex_pos;
	int tex_n;

} t_ray;
typedef struct s_img
{
	void *img;
	int *data;
	char *path;
	int width;
	int height;
	int endian;
	int len;
	int bpp;
} t_img;

typedef struct s_colors
{
	int red;
	int green;
	int blue;
	int alpha;
} t_colors;

typedef struct s_map
{
	int **map;
	size_t map_width;
	size_t map_height;
	int floor_hex;
	int ceil_hex;
	t_colors floor;
	t_colors sky;
} t_map;

typedef struct s_game
{
	void *mlx;
	void *mlx_win;
	void *img;
	int **tex_buf;
	int **texture;
	int fd;
	char *path_texture[4];
	t_map map;
	t_player player;
	t_img image;
	t_ray ray;

} t_game;

int handle_raycasting(t_game *game);
void init_raycast_variables(t_game *game, t_ray *ray, int x);
void looping_rays(t_game *game);
void wall_distance(t_game *game);
void wall_height(t_game *game);
int handle_keys(int keycode, t_game *game);
int end_program(void *l);
// int to_rgba(int r, int g, int b, int alpha);
// void print_pixel(t_img img, int x, int y, int color);
void pixel_map(t_game *game);
void    load_imgs(t_game *game, t_parser *parser);
void    draw_img(t_game *game):
void initialize_tex_buff(t_game *game);


extern int worldMap[24][24];

#endif