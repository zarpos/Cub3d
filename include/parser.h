/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:52:12 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/27 15:58:57 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

typedef struct s_game	t_game;

typedef enum e_texture
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	Error,
}	t_texture;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}	t_color;

typedef struct s_map
{
	char	**map;
	char	**map_copy;
	int		rows;
	int		cols;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	floor;
	t_color	ceiling;
	int		max_x;
	int		max_y;
	double	player_x;
	double	player_y;
	int		floor_hex;
	int		ceil_hex;
}	t_map;

// FILE VERIFYING
int			open_validated_file(char **argv);
char		**process_file(int fd);
void		verify_blank_line(char *line);
char		**check_args(int argc, char **argv);
char		*convert_lines(int fd);

// CHAR VERIFYING
int			check_chars(t_game *game, char value, int x, int y);
void		check_map_chars(t_game *game, char **map);
void		parsing(int argc, char **argv, t_game *game);

// TEXTURE VERIFYING
char		*get_texture(char *line);
t_color		read_colors(char *line);
void		set_texture(t_game *game, char **file_con);
t_texture	read_texture(char *line);

// GAME VERIFYING
int			get_big_line(char **matrix);
void		set_map(char **map, char ***map_cpy);
char		**get_map_cpy(char **map);
void		check_walls(char **map_cpy);
void		check_closed_walls(char **map);

#endif