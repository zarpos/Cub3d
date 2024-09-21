/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:52:12 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/21 22:33:57 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "cub3d.h"

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


#endif