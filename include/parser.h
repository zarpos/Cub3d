/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:52:12 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/23 19:28:26 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "cub3d.h"

typedef enum e_texture
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	Error,
} t_texture;

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
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	t_color	floor;
	t_color	ceiling;
	int		max_x;
	int		max_y;
	int		player_x;
	int		player_y;
}	t_map;


// FILE VERIFYING
int		open_validated_file(char **argv);
char	**process_file(int fd);
void	verify_blank_line(char *line);
char	**check_args(int argc, char **argv);
char	*convert_lines(int fd);

// CHAR VERIFYING
static int	check_chars(t_map *map_data, char value, int x, int y);
static void	check_map_chars(t_map *map_data, char **map);
void		parsing(int argc, char **argv, t_map *map_data);

// TEXTURE VERIFYING
t_texture	read_texture(char *line);
char		*get_texture(char *line);
t_color		read_colors(char *line);
void		set_texture(t_game *game, char **file_con);

// GAME VERIFYING
static int	get_big_line(char **matrix);
static void	set_map(char **map, char ***map_cpy);
static char	**get_map_cpy(char **map);
static void	check_walls(char **map_cpy);
void		check_closed_walls(char **map);

#endif