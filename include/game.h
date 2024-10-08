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
# define GAME_H

# include "cub3d.h"

# define MOSSY "./src/sprites/mossy.xpm"
# define PURPLE "./src/sprites/purplestone.xpm"
# define BRICK "./src/sprites/redbrick.xpm"
# define WOOD "./src/sprites/wood.xpm"
# define SCREEN_X 800
# define SCREEN_Y 600
# define KEY_PRESS 2
# define KEY_OFF 3
# define W 119
# define A 97
# define S 115
# define D 100

# define K_ESC 65307
# define DESTROY 17

# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361

# define TEXWIDTH 64
# define TEXHEIGHT 64

# define FORWARD 1
# define BACKWARD -1

# define TEXTURE_NORTH 0
# define TEXTURE_SOUTH 1
# define TEXTURE_WEST 2
# define TEXTURE_EAST 3

# define TEX_SIZE 64

# define FLOOR_PATH "../sprites/mossy.xpm"
# define WALL_PATH "./sprites/wood.xpm"

# define NAME "CUB</3D"

typedef struct s_player
{
	double	dir_x;
	double	dir_y;
	double	move_speed;
	double	rot_speed;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int	a;
	int	w;
	int	d;
	int	s;
	int	right;
	int	left;
	int	esc;
}	t_keys;

typedef struct s_ray
{
	double	cam_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	int		side;
	int		hit;
	int		height;
	int		lh;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_n;

}	t_ray;

typedef struct s_img
{
	void	*img;
	int		*data;
	char	*path;
	int		width;
	int		height;
	int		endian;
	int		len;
	int		bpp;
}	t_img;

typedef struct s_colors
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}	t_colors;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	int			**tex_buf;
	int			**texture;
	int			fd;
	char		*path_texture[4];
	t_map		map_data;
	t_player	player;
	t_img		image;
	t_ray		ray;
	t_keys		keys;

}	t_game;

void	init_values(t_game *game);
void	draw_foor_ceiling(t_game *game);
int		main_loop(t_game *game);
int		handle_raycasting(t_game *game);
void	init_raycast_variables(t_game *game, t_ray *ray, int x);
void	looping_rays(t_game *game, t_ray *ray);
void	wall_distance(t_game *game, t_ray *ray);
void	wall_height(t_game *game, t_ray *ray);
int		handle_movements(t_game *game);
int		end_program(void *l);
void	pixel_map(t_game *game);
void	load_imgs(t_game *game);
void	draw_img(t_game *game);
void	initialize_tex_buff(t_game *game);
void	render_walls(t_game *game, t_ray *ray, int x, int y);

#endif